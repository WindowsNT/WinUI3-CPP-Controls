#pragma once
#include "RangeSelect.g.h"

namespace winrt::Sample::implementation
{
    struct RangeSelect : RangeSelectT<RangeSelect>
    {
        RangeSelect();

        double Minimum();
        void Minimum(double value);

        double Maximum();
        void Maximum(double value);

        double StartValue();
        void StartValue(double value);

        double EndValue();
        void EndValue(double value);

        Microsoft::UI::Xaml::Controls::Orientation Orientation();
        void Orientation(Microsoft::UI::Xaml::Controls::Orientation value);

        static Microsoft::UI::Xaml::DependencyProperty MinimumProperty();
        static Microsoft::UI::Xaml::DependencyProperty MaximumProperty();
        static Microsoft::UI::Xaml::DependencyProperty StartValueProperty();
        static Microsoft::UI::Xaml::DependencyProperty EndValueProperty();
        static Microsoft::UI::Xaml::DependencyProperty OrientationProperty();

        winrt::event_token RangeChanged(Windows::Foundation::TypedEventHandler<Sample::RangeSelect, Windows::Foundation::IInspectable> const& handler);
        void RangeChanged(winrt::event_token const& token) noexcept;

        void OnApplyTemplate();

    private:
        static Microsoft::UI::Xaml::DependencyProperty m_minimumProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_maximumProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_startValueProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_endValueProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_orientationProperty;

        Microsoft::UI::Xaml::Controls::Primitives::Thumb m_startThumb{ nullptr };
        Microsoft::UI::Xaml::Controls::Primitives::Thumb m_endThumb{ nullptr };
        Microsoft::UI::Xaml::Shapes::Rectangle m_rangeRect{ nullptr };

        void OnStartThumbDragDelta(IInspectable const&, Microsoft::UI::Xaml::Controls::Primitives::DragDeltaEventArgs const& e);
        void OnEndThumbDragDelta(IInspectable const&, Microsoft::UI::Xaml::Controls::Primitives::DragDeltaEventArgs const& e);
        void UpdateThumbs();

        winrt::event<Windows::Foundation::TypedEventHandler<Sample::RangeSelect, Windows::Foundation::IInspectable>> m_rangeChangedEvent;
    };
}
namespace winrt::Sample::factory_implementation
{
    struct RangeSelect : RangeSelectT<RangeSelect, implementation::RangeSelect> {};
}
