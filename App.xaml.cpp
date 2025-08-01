#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"





using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;


winrt::Sample::MainWindow CreateWi()
{
    winrt::Sample::MainWindow j;
    j.Activate();
	j.ExtendsContentIntoTitleBar(true);
    return j;
}








namespace winrt::Sample::implementation
{
    /// <summary>
    /// Initializes the singleton application object.  This is the first line of authored code
    /// executed, and as such is the logical equivalent of main() or WinMain().
    /// </summary>
    App::App()
    {
#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
        {
            if (IsDebuggerPresent())
            {
                auto errorMessage = e.Message();
                __debugbreak();
            }
        });
#endif
    }

    /// <summary>
    /// Invoked when the application is launched.
    /// </summary>
    /// <param name="e">Details about the launch request and process.</param>
    void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
    {
        window = CreateWi();
    }
}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, [[maybe_unused]] PWSTR t, int)
{
    CoInitializeEx(0, COINIT_APARTMENTTHREADED);
    {
        void (WINAPI * pfnXamlCheckProcessRequirements)();
        auto module = ::LoadLibrary(L"Microsoft.ui.xaml.dll");
        if (module)
        {
            pfnXamlCheckProcessRequirements = reinterpret_cast<decltype(pfnXamlCheckProcessRequirements)>(GetProcAddress(module, "XamlCheckProcessRequirements"));
            if (pfnXamlCheckProcessRequirements)
            {
                (*pfnXamlCheckProcessRequirements)();
            }

            ::FreeLibrary(module);
        }
    }

    winrt::init_apartment(winrt::apartment_type::single_threaded);
    ::winrt::Microsoft::UI::Xaml::Application::Start(
        [](auto&&)
        {
            ::winrt::make<::winrt::Sample::implementation::App>();
        });

    return 0;
}

