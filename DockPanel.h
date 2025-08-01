#pragma once
#include "DockPanel.g.h"

namespace winrt::Sample::implementation
{
    struct DockPanel : DockPanelT<DockPanel>
    {
        DockPanel();

        static Microsoft::UI::Xaml::DependencyProperty DockProperty();


        static void SetDock(Microsoft::UI::Xaml::UIElement const& element, Sample::Dock const& value);
        static Sample::Dock GetDock(Microsoft::UI::Xaml::UIElement const& element);

        winrt::Windows::Foundation::Size ArrangeOverride(winrt::Windows::Foundation::Size finalSize);
        winrt::Windows::Foundation::Size MeasureOverride(winrt::Windows::Foundation::Size availableSize);

    private:
        static Microsoft::UI::Xaml::DependencyProperty m_dockProperty;
    };
}
namespace winrt::Sample::factory_implementation
{
    struct DockPanel : DockPanelT<DockPanel, implementation::DockPanel> {};
}
