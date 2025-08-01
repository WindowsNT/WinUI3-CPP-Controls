#include "pch.h"
#include "DockPanel.h"
#include "DockPanel.g.cpp"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

using namespace winrt;
using namespace Windows::Foundation; 
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using Sample::Dock;

namespace winrt::Sample::implementation
{
    DependencyProperty DockPanel::m_dockProperty =
        DependencyProperty::RegisterAttached(
            L"Dock",
            xaml_typename<Sample::Dock>(),
            xaml_typename<Sample::DockPanel>(),
            PropertyMetadata{ box_value(Sample::Dock::Left) }
        );

    void DockPanel::SetDock(Microsoft::UI::Xaml::UIElement const& element, Sample::Dock const& value)
    {
        element.SetValue(m_dockProperty, winrt::box_value(value));
    }

    Sample::Dock DockPanel::GetDock(Microsoft::UI::Xaml::UIElement const& element)
    {
        return winrt::unbox_value<Sample::Dock>(element.GetValue(m_dockProperty));
    }

    DockPanel::DockPanel() {}

    DependencyProperty DockPanel::DockProperty()
    {
        return m_dockProperty;
    }

    winrt::Windows::Foundation::Size DockPanel::MeasureOverride(winrt::Windows::Foundation::Size availableSize)
    {
        winrt::Windows::Foundation::Size usedSize{ 0, 0 };
        for (auto const& child : Children())
        {
            child.Measure(availableSize);
        }
        return availableSize;
    }

    winrt::Windows::Foundation::Size DockPanel::ArrangeOverride(winrt::Windows::Foundation::Size finalSize)
    {
        double left = 0, top = 0, right = finalSize.Width, bottom = finalSize.Height;

        for (auto const& child : Children())
        {
            auto dock = winrt::unbox_value<Dock>(child.GetValue(m_dockProperty));
            winrt::Windows::Foundation::Size desired = child.DesiredSize();

            Rect rect{};
            switch (dock)
            {
            case Dock::Left:
                rect = { (float)left, (float)top, (float)desired.Width, (float)finalSize.Height };
                left += desired.Width;
                break;
            case Dock::Right:
                rect = { (float)(right - desired.Width), (float)top, (float)desired.Width, (float)finalSize.Height };
                right -= desired.Width;
                break;
            case Dock::Top:
                rect = { (float)left, (float)top, (float)finalSize.Width, (float)desired.Height };
                top += desired.Height;
                break;
            case Dock::Bottom:
                rect = { (float)left, (float)(bottom - desired.Height), finalSize.Width, desired.Height };
                bottom -= desired.Height;
                break;
            }

            child.Arrange(rect);
        }
		return finalSize;
    }
}
