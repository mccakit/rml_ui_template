#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <RmlUi_Backend.h>
#include <chrono>
#include <thread>

bool ProcessKeyDownShortcuts(Rml::Context *context, Rml::Input::KeyIdentifier key, int key_modifier,
                             float native_dp_ratio, bool priority)
{
    if (!context)
        return true;

    // Result should return true to allow the event to propagate to the next handler.
    bool result = false;

    // This function is intended to be called twice by the backend, before and after submitting the key event to the
    // context. This way we can intercept shortcuts that should take priority over the context, and then handle any
    // shortcuts of lower priority if the context did not intercept it.
    if (priority)
    {
        // Priority shortcuts are handled before submitting the key to the context.

        // Toggle debugger and set dp-ratio using Ctrl +/-/0 keys.
        if (key == Rml::Input::KI_F8)
        {
            Rml::Debugger::SetVisible(!Rml::Debugger::IsVisible());
        }
        else if (key == Rml::Input::KI_0 && key_modifier & Rml::Input::KM_CTRL)
        {
            context->SetDensityIndependentPixelRatio(native_dp_ratio);
        }
        else if (key == Rml::Input::KI_1 && key_modifier & Rml::Input::KM_CTRL)
        {
            context->SetDensityIndependentPixelRatio(1.f);
        }
        else if ((key == Rml::Input::KI_OEM_MINUS || key == Rml::Input::KI_SUBTRACT) &&
                 key_modifier & Rml::Input::KM_CTRL)
        {
            const float new_dp_ratio = Rml::Math::Max(context->GetDensityIndependentPixelRatio() / 1.2f, 0.5f);
            context->SetDensityIndependentPixelRatio(new_dp_ratio);
        }
        else if ((key == Rml::Input::KI_OEM_PLUS || key == Rml::Input::KI_ADD) && key_modifier & Rml::Input::KM_CTRL)
        {
            const float new_dp_ratio = Rml::Math::Min(context->GetDensityIndependentPixelRatio() * 1.2f, 2.5f);
            context->SetDensityIndependentPixelRatio(new_dp_ratio);
        }
        else
        {
            // Propagate the key down event to the context.
            result = true;
        }
    }
    else
    {
        // We arrive here when no priority keys are detected and the key was not consumed by the context. Check for
        // shortcuts of lower priority.
        if (key == Rml::Input::KI_R && key_modifier & Rml::Input::KM_CTRL)
        {
            for (int i = 0; i < context->GetNumDocuments(); i++)
            {
                Rml::ElementDocument *document = context->GetDocument(i);
                const Rml::String &src = document->GetSourceURL();
                if (src.size() > 4 && src.substr(src.size() - 4) == ".rml")
                {
                    document->ReloadStyleSheet();
                }
            }
        }
        else
        {
            result = true;
        }
    }

    return result;
}
int main()
{
    const int window_width = 1024;
    const int window_height = 768;
    Backend::Initialize("Load Document Sample", window_width, window_height, true);
    Rml::SetSystemInterface(Backend::GetSystemInterface());
    Rml::SetRenderInterface(Backend::GetRenderInterface());
    Rml::Initialise();
    Rml::Context *context = Rml::CreateContext("main", Rml::Vector2i(window_width, window_height));
    Rml::Debugger::Initialise(context);
    Rml::LoadFontFace("LatoLatin-Regular.ttf");
    Rml::LoadFontFace("LatoLatin-Italic.ttf");
    Rml::LoadFontFace("LatoLatin-Bold.ttf");
    Rml::LoadFontFace("LatoLatin-BoldItalic.ttf");
    Rml::ElementDocument *document = context->LoadDocument("demo.rml");
    document->Show();
    bool running = true;
    while (running)
    {
        running = Backend::ProcessEvents(context, &ProcessKeyDownShortcuts, true);
        context->Update();
        Backend::BeginFrame();
        context->Render();
        Backend::PresentFrame();
        std::this_thread::sleep_for(std::chrono::seconds(1 / 60));
    }
    Rml::Shutdown();
    Backend::Shutdown();
    return 0;
}
