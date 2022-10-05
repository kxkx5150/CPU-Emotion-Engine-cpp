#include <SDL2/SDL.h>
#include <cstdio>
#include <zstd_zlibwrapper.h>

#include "GSH_OpenGLSDL.h"
#include "Ps2VmSDL2.h"
#include "AppConfig.h"
#include "DiskUtils.h"
#include "PathUtils.h"
#include "PS2VM_Preferences.h"


#define PREFERENCE_AUDIO_ENABLEOUTPUT "audio.enableoutput"
#define PREF_UI_SHOWEECPUUSAGE        "ui.showeecpuusage"
#define PREF_UI_PAUSEWHENFOCUSLOST    "ui.pausewhenfocuslost"
#define PREF_UI_SHOWEXITCONFIRMATION  "ui.showexitconfirmation"
#define PREF_VIDEO_GS_HANDLER         "video.gshandler"
#define PREF_INPUT_PAD1_PROFILE       "input.pad1.profile"


int main(int argc, char *argv[])
{
    bool Running = true;
    int  width = 640, height = 480;

    SDL_Window *glwind =
        SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    SDL_Renderer *render = SDL_CreateRenderer(glwind, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetScale(render, 1, 1);


    CPs2VmSDL2 *g_virtualMachine = new CPs2VmSDL2(glwind, width, height);
    g_virtualMachine->BootDiscImage(argv[1]);

    while (Running) {
        SDL_Event   Event;
        SDL_Keycode Key;

        while (SDL_PollEvent(&Event)) {
            switch (Event.type) {
                case SDL_QUIT:
                    Running = 0;
                    break;
                case SDL_KEYDOWN:
                    Key = Event.key.keysym.sym;
                    g_virtualMachine->keyPressEvent(Key);
                    break;

                case SDL_KEYUP:
                    Key = Event.key.keysym.sym;
                    g_virtualMachine->keyReleaseEvent(Key);
                    break;
            }
        }
    }


    if (g_virtualMachine != nullptr) {
        g_virtualMachine->Pause();
        // m_qtKeyInputProvider.reset();
        g_virtualMachine->DestroyPadHandler();
        g_virtualMachine->DestroyGSHandler();
        g_virtualMachine->DestroySoundHandler();
        g_virtualMachine->Destroy();
        delete g_virtualMachine;
        g_virtualMachine = nullptr;
    }
    return 0;
}