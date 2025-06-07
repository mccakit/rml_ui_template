#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <RmlUi_Backend.h>
#include <thread>
#include <chrono>

int main()
{
	const int window_width = 1024;
	const int window_height = 768;
	if (!Backend::Initialize("Load Document Sample", window_width, window_height, true))
	{
		return -1;
	}
	Rml::SetSystemInterface(Backend::GetSystemInterface());
	Rml::SetRenderInterface(Backend::GetRenderInterface());
	Rml::Initialise();
	Rml::Context* context = Rml::CreateContext("main", Rml::Vector2i(window_width, window_height));
	if (!context)
	{
		Rml::Shutdown();
		Backend::Shutdown();
		return -1;
	}
	Rml::Debugger::Initialise(context);
	Rml::LoadFontFace("LatoLatin-Regular.ttf");
	Rml::LoadFontFace("LatoLatin-Italic.ttf");
	Rml::LoadFontFace("LatoLatin-Bold.ttf");
	Rml::LoadFontFace("LatoLatin-BoldItalic.ttf");
	if (Rml::ElementDocument* document = context->LoadDocument("demo.rml"))
	{
	    document->Show();
	}
	while (true)
	{
		context->Update();
		Backend::BeginFrame();
		context->Render();
		Backend::PresentFrame();
		std::this_thread::sleep_for(std::chrono::seconds(1/60));
	}
	Rml::Shutdown();
	Backend::Shutdown();
	return 0;
}
