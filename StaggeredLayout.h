#pragma once
#include "StaggeredLayout.g.h"

namespace winrt::Sample::implementation
{
    struct StaggeredLayout : StaggeredLayoutT<StaggeredLayout>
    {
        StaggeredLayout() = default;

        Windows::Foundation::Size MeasureOverride(
            Microsoft::UI::Xaml::Controls::VirtualizingLayoutContext const& context,
            Windows::Foundation::Size const& availableSize);

        Windows::Foundation::Size ArrangeOverride(
            Microsoft::UI::Xaml::Controls::VirtualizingLayoutContext const& context,
            Windows::Foundation::Size const& finalSize);

        int32_t ColumnCount()
        {
            return winrt::unbox_value<int32_t>(GetValue(m_columnCountProperty));
        }

        void ColumnCount(int32_t value)
        {
            SetValue(m_columnCountProperty, winrt::box_value(value));
        }

        static Microsoft::UI::Xaml::DependencyProperty ColumnCountProperty()
        {
            return m_columnCountProperty;
        }

    private:
        static Microsoft::UI::Xaml::DependencyProperty m_columnCountProperty;

    private:
        double m_spacing{ 8.0 };
    };
}

namespace winrt::Sample::factory_implementation
{
    struct StaggeredLayout : StaggeredLayoutT<StaggeredLayout, implementation::StaggeredLayout> {};
}
