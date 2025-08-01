#pragma once
#include "Resizer.g.h"

namespace winrt::Sample::implementation
{
    struct Resizer : ResizerT<Resizer>
    {
        Resizer();

        // Property getters/setters
        double Value() const { return winrt::unbox_value<double>(GetValue(m_valueProperty)); }
        void Value(double const& value) { SetValue(m_valueProperty, winrt::box_value(value)); }

        double Minimum() const { return winrt::unbox_value<double>(GetValue(m_minimumProperty)); }
        void Minimum(double const& value) { SetValue(m_minimumProperty, winrt::box_value(value)); }

        double Maximum() const { return winrt::unbox_value<double>(GetValue(m_maximumProperty)); }
        void Maximum(double const& value) { SetValue(m_maximumProperty, winrt::box_value(value)); }

        // Static property accessors
        static Microsoft::UI::Xaml::DependencyProperty ValueProperty() { return m_valueProperty; }
        static Microsoft::UI::Xaml::DependencyProperty MinimumProperty() { return m_minimumProperty; }
        static Microsoft::UI::Xaml::DependencyProperty MaximumProperty() { return m_maximumProperty; }


        Sample::SplitOrientation Orientation() const;
        void Orientation(Sample::SplitOrientation const& value);

        static Microsoft::UI::Xaml::DependencyProperty OrientationProperty();
        static Microsoft::UI::Xaml::DependencyProperty m_orientationProperty;

        // Events
        winrt::event_token ValueChanged(Windows::Foundation::TypedEventHandler<Sample::Resizer, Windows::Foundation::IInspectable> const& handler);
        void ValueChanged(winrt::event_token const& token) noexcept;

        void OnApplyTemplate() ;
        void OnPointerPressed(winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e) ;
        void OnPointerMoved(Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e) ;
        void OnPointerReleased(Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e) ;
        void OnPointerCaptureLost(Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e) ;

        static Microsoft::UI::Xaml::DependencyProperty m_valueProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_minimumProperty;
        static Microsoft::UI::Xaml::DependencyProperty m_maximumProperty;

        static void OnValuePropertyChanged(Microsoft::UI::Xaml::DependencyObject const& d, Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

        bool m_isDragging{ false };
        Windows::Foundation::Point m_lastPointerPosition{};
        double m_dragStartValue{ 0.0 };

        winrt::event<Windows::Foundation::TypedEventHandler<Sample::Resizer, Windows::Foundation::IInspectable>> m_valueChangedEvent;


        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
        {
            return m_propertyChanged.add(handler);
        }
        void PropertyChanged(winrt::event_token const& token) noexcept
        {
            m_propertyChanged.remove(token);
        }
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;


    };
}
namespace winrt::Sample::factory_implementation
{
    struct Resizer : ResizerT<Resizer, implementation::Resizer>
    {
    };
}
