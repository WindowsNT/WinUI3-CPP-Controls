#include "pch.h"
#include "RangeSelect.h"
#include "RangeSelect.g.cpp"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::Sample::implementation
{
    DependencyProperty RangeSelect::m_minimumProperty =
        DependencyProperty::Register(L"Minimum", xaml_typename<double>(), xaml_typename<Sample::RangeSelect>(), PropertyMetadata{ box_value(0.0) });

    DependencyProperty RangeSelect::m_maximumProperty =
        DependencyProperty::Register(L"Maximum", xaml_typename<double>(), xaml_typename<Sample::RangeSelect>(), PropertyMetadata{ box_value(100.0) });

    DependencyProperty RangeSelect::m_startValueProperty =
        DependencyProperty::Register(L"StartValue", xaml_typename<double>(), xaml_typename<Sample::RangeSelect>(), PropertyMetadata{ box_value(25.0) });

    DependencyProperty RangeSelect::m_endValueProperty =
        DependencyProperty::Register(L"EndValue", xaml_typename<double>(), xaml_typename<Sample::RangeSelect>(), PropertyMetadata{ box_value(75.0) });

    DependencyProperty RangeSelect::m_orientationProperty =
        DependencyProperty::Register(L"Orientation", xaml_typename<Controls::Orientation>(), xaml_typename<Sample::RangeSelect>(), PropertyMetadata{ box_value(Controls::Orientation::Horizontal) });

    RangeSelect::RangeSelect()
    {
        DefaultStyleKey(box_value(L"Sample.RangeSelect"));
    }

    void RangeSelect::OnApplyTemplate()
    {
        __super::OnApplyTemplate();

        m_startThumb = GetTemplateChild(L"StartThumb").try_as<Controls::Primitives::Thumb>();
        m_endThumb = GetTemplateChild(L"EndThumb").try_as<Controls::Primitives::Thumb>();
        m_rangeRect = GetTemplateChild(L"RangeHighlight").try_as<Shapes::Rectangle>();

        if (m_startThumb)
            m_startThumb.DragDelta({ this, &RangeSelect::OnStartThumbDragDelta });

        if (m_endThumb)
            m_endThumb.DragDelta({ this, &RangeSelect::OnEndThumbDragDelta });

        UpdateThumbs();
    }

    double RangeSelect::Minimum() { return unbox_value<double>(GetValue(m_minimumProperty)); }
    void RangeSelect::Minimum(double value) { SetValue(m_minimumProperty, box_value(value)); }

    double RangeSelect::Maximum() { return unbox_value<double>(GetValue(m_maximumProperty)); }
    void RangeSelect::Maximum(double value) { SetValue(m_maximumProperty, box_value(value)); }

    double RangeSelect::StartValue() { return unbox_value<double>(GetValue(m_startValueProperty)); }
    void RangeSelect::StartValue(double value) { SetValue(m_startValueProperty, box_value(value)); }

    double RangeSelect::EndValue() { return unbox_value<double>(GetValue(m_endValueProperty)); }
    void RangeSelect::EndValue(double value) { SetValue(m_endValueProperty, box_value(value)); }

    Controls::Orientation RangeSelect::Orientation() { return unbox_value<Controls::Orientation>(GetValue(m_orientationProperty)); }
    void RangeSelect::Orientation(Controls::Orientation value) { SetValue(m_orientationProperty, box_value(value)); }

    DependencyProperty RangeSelect::MinimumProperty() { return m_minimumProperty; }
    DependencyProperty RangeSelect::MaximumProperty() { return m_maximumProperty; }
    DependencyProperty RangeSelect::StartValueProperty() { return m_startValueProperty; }
    DependencyProperty RangeSelect::EndValueProperty() { return m_endValueProperty; }
    DependencyProperty RangeSelect::OrientationProperty() { return m_orientationProperty; }

    void RangeSelect::OnStartThumbDragDelta(IInspectable const&, Controls::Primitives::DragDeltaEventArgs const& e)
    {
        double delta = Orientation() == Controls::Orientation::Horizontal ? e.HorizontalChange() : e.VerticalChange();
        double size = Orientation() == Controls::Orientation::Horizontal ? ActualWidth() : ActualHeight();
        double range = Maximum() - Minimum();
        double offset = delta / size * range;
        double newValue = std::clamp(StartValue() + offset, Minimum(), EndValue());
        StartValue(newValue);
        UpdateThumbs();
        m_rangeChangedEvent(*this, nullptr);
    }

    void RangeSelect::OnEndThumbDragDelta(IInspectable const&, Controls::Primitives::DragDeltaEventArgs const& e)
    {
        double delta = Orientation() == Controls::Orientation::Horizontal ? e.HorizontalChange() : e.VerticalChange();
        double size = Orientation() == Controls::Orientation::Horizontal ? ActualWidth() : ActualHeight();
        double range = Maximum() - Minimum();
        double offset = delta / size * range;
        double newValue = std::clamp(EndValue() + offset, StartValue(), Maximum());
        EndValue(newValue);
        UpdateThumbs();
        m_rangeChangedEvent(*this, nullptr);
    }

    void RangeSelect::UpdateThumbs()
    {
        double size = Orientation() == Controls::Orientation::Horizontal ? ActualWidth() : ActualHeight();
        double range = Maximum() - Minimum();

        double startPos = ((StartValue() - Minimum()) / range) * size;
        double endPos = ((EndValue() - Minimum()) / range) * size;

        if (Orientation() == Controls::Orientation::Horizontal)
        {
            if (m_startThumb) m_startThumb.Margin(ThicknessHelper::FromLengths(startPos - 6, 0, 0, 0));
            if (m_endThumb) m_endThumb.Margin(ThicknessHelper::FromLengths(endPos - 6, 0, 0, 0));
            if (m_rangeRect)
            {
                m_rangeRect.Margin(ThicknessHelper::FromLengths(startPos, 0, 0, 0));
                m_rangeRect.Width(endPos - startPos);
            }
        }
        else
        {
            if (m_startThumb) m_startThumb.Margin(ThicknessHelper::FromLengths(0, startPos - 6, 0, 0));
            if (m_endThumb) m_endThumb.Margin(ThicknessHelper::FromLengths(0, endPos - 6, 0, 0));
            if (m_rangeRect)
            {
                m_rangeRect.Margin(ThicknessHelper::FromLengths(0, startPos, 0, 0));
                m_rangeRect.Height(endPos - startPos);
            }
        }
    }

    winrt::event_token RangeSelect::RangeChanged(Windows::Foundation::TypedEventHandler<Sample::RangeSelect, IInspectable> const& handler)
    {
        return m_rangeChangedEvent.add(handler);
    }

    void RangeSelect::RangeChanged(winrt::event_token const& token) noexcept
    {
        m_rangeChangedEvent.remove(token);
    }
}
