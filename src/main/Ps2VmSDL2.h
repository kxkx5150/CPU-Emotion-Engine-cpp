#pragma once
#include <SDL2/SDL.h>
#include "PS2VM.h"

class CPs2VmSDL2 : public CPS2VM {
  public:
    CPs2VmSDL2(SDL_Window *glwind, int width, int height);

    void CreateVM() override;
    void BootElf(std::string);
    void BootDiscImage(std::string);
};
