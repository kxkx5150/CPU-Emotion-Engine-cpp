#pragma once
#include <SDL2/SDL.h>
#include "gs/GSH_OpenGL/GSH_OpenGL.h"


class CGSH_OpenGLSDL : public CGSH_OpenGL {
  private:
    SDL_Window   *m_context   = nullptr;
    SDL_GLContext m_glcontext = nullptr;

  public:
    CGSH_OpenGLSDL(SDL_Window *window);
    virtual ~CGSH_OpenGLSDL() = default;

    static FactoryFunction GetFactoryFunction(SDL_Window *window);

    void InitializeImpl() override;
    void ReleaseImpl() override;
    void PresentBackbuffer() override;
};
