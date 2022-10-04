#include <cstddef>
#include <cstdio>
#if !defined(GLES_COMPATIBILITY)
#include "GSH_OpenGLSDL.h"
#endif


CGSH_OpenGLSDL::CGSH_OpenGLSDL(SDL_Window *window)
{
    m_context = window;
}
CGSH_OpenGL::FactoryFunction CGSH_OpenGLSDL::GetFactoryFunction(SDL_Window *window)
{
    return [window]() { return new CGSH_OpenGLSDL(window); };
}
void CGSH_OpenGLSDL::InitializeImpl()
{
    m_glcontext = SDL_GL_CreateContext(m_context);
    auto result = glewInit();
    CGSH_OpenGL::InitializeImpl();
}
void CGSH_OpenGLSDL::ReleaseImpl()
{
    SDL_GL_DeleteContext(m_glcontext);
    CGSH_OpenGL::ReleaseImpl();
}
void CGSH_OpenGLSDL::PresentBackbuffer()
{
    SDL_GL_SwapWindow(m_context);
}
