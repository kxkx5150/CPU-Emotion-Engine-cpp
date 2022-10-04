#include "Ps2VmSDL2.h"
#include "Jitter_CodeGen_x86_64.h"
#include "MemoryUtils.h"
#include "BasicBlock.h"
#include "PS2VM_Preferences.h"
#include "AppConfig.h"
#include "GSH_OpenGLSDL.h"



CPs2VmSDL2::CPs2VmSDL2(SDL_Window *glwind, int width, int height)
{
    Initialize();
    CreateGSHandler(CGSH_OpenGLSDL::GetFactoryFunction(glwind));

    CGSHandler::PRESENTATION_PARAMS presentationParams;
    presentationParams.mode         = CGSHandler::PRESENTATION_MODE_FIT;
    presentationParams.windowWidth  = width;
    presentationParams.windowHeight = height;
    m_ee->m_gs->SetPresentationParams(presentationParams);
}
void CPs2VmSDL2::CreateVM()
{
    CPS2VM::CreateVM();
    printf("Initializing PS2VM...\r\n");
}
void CPs2VmSDL2::BootElf(std::string path)
{
    m_mailBox.SendCall([this, path]() {
        printf("Loading '%s'...\r\n", path.c_str());
        try {
            Reset();
            m_ee->m_os->BootFromFile(path);
        } catch (const std::exception &ex) {
            printf("Failed to start: %s.\r\n", ex.what());
            return;
        }
        printf("Starting...\r\n");
        ResumeImpl();
    });
}
void CPs2VmSDL2::BootDiscImage(std::string path)
{
    m_mailBox.SendCall([this, path]() {
        printf("Loading '%s'...\r\n", path.c_str());
        try {
            CAppConfig::GetInstance().SetPreferencePath(PREF_PS2_CDROM0_PATH, path);
            Reset();
            m_ee->m_os->BootFromCDROM();
        } catch (const std::exception &ex) {
            printf("Failed to start: %s.\r\n", ex.what());
            return;
        }
        printf("Starting...\r\n");
        ResumeImpl();
    });
}