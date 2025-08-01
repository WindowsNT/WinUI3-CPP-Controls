#include "pch.h"
#include "Resizer.h"
#include "Resizer.g.cpp"


using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;
using namespace Microsoft::UI::Xaml::Input;
using namespace Windows::Foundation;

namespace winrt::Sample::implementation
{
        // Static dependency property definitions
    DependencyProperty Resizer::m_valueProperty =
        DependencyProperty::Register(
            L"Value",
            xaml_typename<double>(),
            xaml_typename<Sample::Resizer>(),
            PropertyMetadata{ box_value(0.0), PropertyChangedCallback{ &Resizer::OnValuePropertyChanged } }
        );

    DependencyProperty Resizer::m_minimumProperty =
        DependencyProperty::Register(
            L"Minimum",
            xaml_typename<double>(),
            xaml_typename<Sample::Resizer>(),
            PropertyMetadata{ box_value(0.0) }
        );

    DependencyProperty Resizer::m_maximumProperty =
        DependencyProperty::Register(
            L"Maximum",
            xaml_typename<double>(),
            xaml_typename<Sample::Resizer>(),
            PropertyMetadata{ box_value(1000.0) }
        );


    DependencyProperty Resizer::m_orientationProperty =
        DependencyProperty::Register(
            L"Orientation",
            xaml_typename<Sample::SplitOrientation>(),
            xaml_typename<Sample::Resizer>(),
            PropertyMetadata{ box_value(Sample::SplitOrientation::Vertical) }
        );

    Resizer::Resizer()
    {
        DefaultStyleKey(winrt::box_value(L"Sample.Resizer"));
    }

    void Resizer::OnApplyTemplate()
    {
        __super::OnApplyTemplate();

        // Set cursor to indicate draggable behavior
        if (Orientation() == Sample::SplitOrientation::Horizontal)
        ProtectedCursor(winrt::Microsoft::UI::Input::InputSystemCursor::Create(winrt::Microsoft::UI::Input::InputSystemCursorShape::SizeNorthSouth));
		else
        ProtectedCursor(winrt::Microsoft::UI::Input::InputSystemCursor::Create(winrt::Microsoft::UI::Input::InputSystemCursorShape::SizeWestEast));
    }

    Sample::SplitOrientation Resizer::Orientation() const
    {
        return winrt::unbox_value<Sample::SplitOrientation>(GetValue(m_orientationProperty));
    }

    void Resizer::Orientation(Sample::SplitOrientation const& value)
    {
        SetValue(m_orientationProperty, box_value(value));
    }

    DependencyProperty Resizer::OrientationProperty() { return m_orientationProperty; }

    void Resizer::OnPointerPressed(winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        __super::OnPointerPressed(e);

        if (e.Pointer().PointerDeviceType() == Microsoft::UI::Input::PointerDeviceType::Mouse)
        {
            m_isDragging = true;
            m_lastPointerPosition = e.GetCurrentPoint(nullptr).Position();
            m_dragStartValue = Value();

            bool success = CapturePointer(e.Pointer());
            if (!success)
            {
                DebugBreak();
            }
            e.Handled(true);
        }
    }

    void Resizer::OnPointerMoved(winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        __super::OnPointerMoved(e);

        if (Orientation() == Sample::SplitOrientation::Horizontal)
        {
            if (m_isDragging)
            {
                auto currentPosition = e.GetCurrentPoint(nullptr).Position();
                auto diff = currentPosition.Y - m_lastPointerPosition.Y;
                m_dragStartValue += diff;

                // clamp it to min/max
                if (m_dragStartValue < Minimum())
                {
                    auto diff2 = Minimum() - m_dragStartValue;
                    currentPosition.Y += (float)diff2;
                    m_dragStartValue = Minimum();
                }
                else if (m_dragStartValue > Maximum())
                {
                    auto diff2 = m_dragStartValue - Maximum();
                    currentPosition.Y -= (float)diff2;
                    m_dragStartValue = Maximum();
                }

                Value(m_dragStartValue);
                m_lastPointerPosition = currentPosition;
                e.Handled(true);
            }
        }
        else
        {
            if (m_isDragging)
            {
                auto currentPosition = e.GetCurrentPoint(nullptr).Position();
                auto diff = currentPosition.X - m_lastPointerPosition.X;
                m_dragStartValue += diff;

                // clamp it to min/max
                if (m_dragStartValue < Minimum())
                {
                    auto diff2 = Minimum() - m_dragStartValue;
                    currentPosition.X += (float)diff2;
                    m_dragStartValue = Minimum();
                }
                else if (m_dragStartValue > Maximum())
                {
                    auto diff2 = m_dragStartValue - Maximum();
                    currentPosition.X -= (float)diff2;
                    m_dragStartValue = Maximum();
                }

                Value(m_dragStartValue);
                m_lastPointerPosition = currentPosition;
                e.Handled(true);
            }
        }
    }

    void Resizer::OnPointerReleased(winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        __super::OnPointerReleased(e);

        if (m_isDragging)
        {
            m_isDragging = false;
            ReleasePointerCapture(e.Pointer());
            e.Handled(true);
        }
    }

    void Resizer::OnPointerCaptureLost(winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
    {
        __super::OnPointerCaptureLost(e);
        m_isDragging = false;
    }

    void Resizer::OnValuePropertyChanged(DependencyObject const& d, DependencyPropertyChangedEventArgs const& )
    {
        if (auto control = d.try_as<Sample::Resizer>())
        {
            if (auto impl = winrt::get_self<implementation::Resizer>(control))
            {
                impl->m_valueChangedEvent(control, nullptr);
            }
        }
    }

    winrt::event_token Resizer::ValueChanged(TypedEventHandler<Sample::Resizer, IInspectable> const& handler)
    {
        return m_valueChangedEvent.add(handler);
    }

    void Resizer::ValueChanged(winrt::event_token const& token) noexcept
    {
        m_valueChangedEvent.remove(token);
    }

}
