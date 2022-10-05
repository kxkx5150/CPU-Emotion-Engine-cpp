#pragma once
#include <SDL2/SDL.h>
#include "PS2VM.h"
#include "InputProviderQtKey.h"
#include "input/InputBindingManager.h"


class CPs2VmSDL2 : public CPS2VM {
  public:
    std::shared_ptr<CInputProviderQtKey> m_qtKeyInputProvider;

  public:
    CPs2VmSDL2(SDL_Window *glwind, int width, int height);

    void CreateVM() override;
    void BootElf(std::string);
    void BootDiscImage(std::string);

    void keyPressEvent(SDL_Keycode sdlkey);
    void keyReleaseEvent(SDL_Keycode sdlkey);
    void AutoConfigureKeyboard(uint32 padIndex, CInputBindingManager *bindingManager);
};
