#include "Ps2VmSDL2.h"
#include "Jitter_CodeGen_x86_64.h"
#include "MemoryUtils.h"
#include "BasicBlock.h"
#include "PS2VM_Preferences.h"
#include "AppConfig.h"
#include "GSH_OpenGLSDL.h"
#include "input/PH_GenericInput.h"
#include <SDL2/SDL_keycode.h>
#include "Qt_def.h"



CPs2VmSDL2::CPs2VmSDL2(SDL_Window *glwind, int width, int height)
{
    Initialize();
    CreateGSHandler(CGSH_OpenGLSDL::GetFactoryFunction(glwind));
    CreatePadHandler(CPH_GenericInput::GetFactoryFunction());

    CGSHandler::PRESENTATION_PARAMS presentationParams;
    presentationParams.mode         = CGSHandler::PRESENTATION_MODE_FIT;
    presentationParams.windowWidth  = width;
    presentationParams.windowHeight = height;
    m_ee->m_gs->SetPresentationParams(presentationParams);

    CreatePadHandler(CPH_GenericInput::GetFactoryFunction());
    auto  padHandler     = static_cast<CPH_GenericInput *>(GetPadHandler());
    auto &bindingManager = padHandler->GetBindingManager();
    m_qtKeyInputProvider = std::make_shared<CInputProviderQtKey>();
    bindingManager.RegisterInputProvider(m_qtKeyInputProvider);
    AutoConfigureKeyboard(0, &bindingManager);
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
void CPs2VmSDL2::keyPressEvent(SDL_Keycode sdlkey)
{
    if (m_qtKeyInputProvider) {
        switch (sdlkey) {
            case SDLK_RETURN2:
                m_qtKeyInputProvider->OnKeyPress(Key_Return);
                break;
            case SDLK_BACKSPACE:
                m_qtKeyInputProvider->OnKeyPress(Key_Backspace);
                break;

            case SDLK_LEFT:
                m_qtKeyInputProvider->OnKeyPress(Key_Left);
                break;
            case SDLK_RIGHT:
                m_qtKeyInputProvider->OnKeyPress(Key_Right);
                break;
            case SDLK_UP:
                m_qtKeyInputProvider->OnKeyPress(Key_Up);
                break;
            case SDLK_DOWN:
                m_qtKeyInputProvider->OnKeyPress(Key_Down);
                break;

            case SDLK_a:
                m_qtKeyInputProvider->OnKeyPress(Key_A);
                break;
            case SDLK_z:
                m_qtKeyInputProvider->OnKeyPress(Key_Z);
                break;
            case SDLK_s:
                m_qtKeyInputProvider->OnKeyPress(Key_S);
                break;
            case SDLK_x:
                m_qtKeyInputProvider->OnKeyPress(Key_X);
                break;

            case SDLK_1:
                m_qtKeyInputProvider->OnKeyPress(Key_1);
                break;
            case SDLK_2:
                m_qtKeyInputProvider->OnKeyPress(Key_2);
                break;
            case SDLK_3:
                m_qtKeyInputProvider->OnKeyPress(Key_3);
                break;
            case SDLK_4:
                m_qtKeyInputProvider->OnKeyPress(Key_4);
                break;
            case SDLK_5:
                m_qtKeyInputProvider->OnKeyPress(Key_5);
                break;
            case SDLK_6:
                m_qtKeyInputProvider->OnKeyPress(Key_6);
                break;
        }
    }
}
void CPs2VmSDL2::keyReleaseEvent(SDL_Keycode sdlkey)
{
    if (m_qtKeyInputProvider) {
        switch (sdlkey) {

            case SDLK_RETURN2:
                m_qtKeyInputProvider->OnKeyRelease(Key_Return);
                break;
            case SDLK_BACKSPACE:
                m_qtKeyInputProvider->OnKeyRelease(Key_Backspace);
                break;

            case SDLK_LEFT:
                m_qtKeyInputProvider->OnKeyRelease(Key_Left);
                break;
            case SDLK_RIGHT:
                m_qtKeyInputProvider->OnKeyRelease(Key_Right);
                break;
            case SDLK_UP:
                m_qtKeyInputProvider->OnKeyRelease(Key_Up);
                break;
            case SDLK_DOWN:
                m_qtKeyInputProvider->OnKeyRelease(Key_Down);
                break;

            case SDLK_a:
                m_qtKeyInputProvider->OnKeyRelease(Key_A);
                break;
            case SDLK_z:
                m_qtKeyInputProvider->OnKeyRelease(Key_Z);
                break;
            case SDLK_s:
                m_qtKeyInputProvider->OnKeyRelease(Key_S);
                break;
            case SDLK_x:
                m_qtKeyInputProvider->OnKeyRelease(Key_X);
                break;

            case SDLK_1:
                m_qtKeyInputProvider->OnKeyRelease(Key_1);
                break;
            case SDLK_2:
                m_qtKeyInputProvider->OnKeyRelease(Key_2);
                break;
            case SDLK_3:
                m_qtKeyInputProvider->OnKeyRelease(Key_3);
                break;
            case SDLK_4:
                m_qtKeyInputProvider->OnKeyRelease(Key_4);
                break;
            case SDLK_5:
                m_qtKeyInputProvider->OnKeyRelease(Key_5);
                break;
            case SDLK_6:
                m_qtKeyInputProvider->OnKeyRelease(Key_6);
                break;
        }
    }
}
void CPs2VmSDL2::AutoConfigureKeyboard(uint32 padIndex, CInputBindingManager *bindingManager)
{
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::START,
                                     CInputProviderQtKey::MakeBindingTarget(Key_Return));
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::SELECT,
                                     CInputProviderQtKey::MakeBindingTarget(Key_Backspace));

    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::DPAD_LEFT,
                                     CInputProviderQtKey::MakeBindingTarget(Key_Left));
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::DPAD_RIGHT,
                                     CInputProviderQtKey::MakeBindingTarget(Key_Right));
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::DPAD_UP,
                                     CInputProviderQtKey::MakeBindingTarget(Key_Up));
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::DPAD_DOWN,
                                     CInputProviderQtKey::MakeBindingTarget(Key_Down));

    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::SQUARE,
                                     CInputProviderQtKey::MakeBindingTarget(Key_A));
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::CROSS,
                                     CInputProviderQtKey::MakeBindingTarget(Key_Z));
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::TRIANGLE,
                                     CInputProviderQtKey::MakeBindingTarget(Key_S));
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::CIRCLE,
                                     CInputProviderQtKey::MakeBindingTarget(Key_X));

    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::L1, CInputProviderQtKey::MakeBindingTarget(Key_1));
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::L2, CInputProviderQtKey::MakeBindingTarget(Key_2));
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::L3, CInputProviderQtKey::MakeBindingTarget(Key_3));
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::R1, CInputProviderQtKey::MakeBindingTarget(Key_8));
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::R2, CInputProviderQtKey::MakeBindingTarget(Key_9));
    bindingManager->SetSimpleBinding(padIndex, PS2::CControllerInfo::R3, CInputProviderQtKey::MakeBindingTarget(Key_0));

    // bindingManager->SetSimulatedAxisBinding(padIndex, PS2::CControllerInfo::ANALOG_LEFT_X,
    //                                         CInputProviderQtKey::MakeBindingTarget(Key_F),
    //                                         CInputProviderQtKey::MakeBindingTarget(Key_H));
    // bindingManager->SetSimulatedAxisBinding(padIndex, PS2::CControllerInfo::ANALOG_LEFT_Y,
    //                                         CInputProviderQtKey::MakeBindingTarget(Key_T),
    //                                         CInputProviderQtKey::MakeBindingTarget(Key_G));

    // bindingManager->SetSimulatedAxisBinding(padIndex, PS2::CControllerInfo::ANALOG_RIGHT_X,
    //                                         CInputProviderQtKey::MakeBindingTarget(Key_J),
    //                                         CInputProviderQtKey::MakeBindingTarget(Key_L));
    // bindingManager->SetSimulatedAxisBinding(padIndex, PS2::CControllerInfo::ANALOG_RIGHT_Y,
    //                                         CInputProviderQtKey::MakeBindingTarget(Key_I),
    //                                         CInputProviderQtKey::MakeBindingTarget(Key_K));
}