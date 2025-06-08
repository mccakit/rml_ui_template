#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <RmlUi_Backend.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

struct AppState
{
    Rml::Context *context;
    Rml::ElementDocument *document;
};

AppState state{};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    Backend::Initialize("Load Document Sample", 1024, 768, true);
    Rml::SetSystemInterface(Backend::GetSystemInterface());
    Rml::SetRenderInterface(Backend::GetRenderInterface());
    Rml::Initialise();

    state.context = Rml::CreateContext("main", Rml::Vector2i(1024, 768));
    Rml::Debugger::Initialise(state.context);

    size_t font_size;
    void *font_data = SDL_LoadFile("LatoLatin-Regular.ttf", &font_size);
    Rml::Span<const Rml::byte> font_span(static_cast<const Rml::byte *>(font_data), font_size);
    Rml::LoadFontFace(font_span, "LatoLatin", Rml::Style::FontStyle::Normal, Rml::Style::FontWeight::Normal);
    char *doc_data = static_cast<char *>(SDL_LoadFile("demo.rml", nullptr));
    state.document = state.context->LoadDocumentFromMemory(doc_data);
    state.document->Show();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    state.context->Update();
    Backend::BeginFrame();
    state.context->Render();
    Backend::PresentFrame();

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    Rml::Shutdown();
    Backend::Shutdown();
}
