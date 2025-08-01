#include "pch.h"
#include "StaggeredLayout.h"
#include "StaggeredLayout.g.cpp"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Microsoft::UI::Xaml::Controls;

namespace winrt::Sample::implementation
{

    Microsoft::UI::Xaml::DependencyProperty StaggeredLayout::m_columnCountProperty =
        Microsoft::UI::Xaml::DependencyProperty::Register(
            L"ColumnCount",
            winrt::xaml_typename<int32_t>(),
            winrt::xaml_typename<Sample::StaggeredLayout>(),
            Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(2) } // default: 2 columns
        );

    Size StaggeredLayout::MeasureOverride(
        VirtualizingLayoutContext const& context,
        Size const& availableSize)
    {

        uint32_t itemCount = context.ItemCount();
        std::vector<double> columnHeights(ColumnCount(), 0.0);
        double columnWidth = availableSize.Width / ColumnCount();

        for (uint32_t i = 0; i < itemCount; ++i)
        {
            auto element = context.GetOrCreateElementAt(i);
            element.Measure({ (float)columnWidth, availableSize.Height });
            auto height = element.DesiredSize().Height;

            auto minColumn = std::min_element(columnHeights.begin(), columnHeights.end()) - columnHeights.begin();
            columnHeights[minColumn] += height + m_spacing;
        }

        double maxHeight = *std::max_element(columnHeights.begin(), columnHeights.end());
        return { availableSize.Width, (float)maxHeight };
    }

    Size StaggeredLayout::ArrangeOverride(
        VirtualizingLayoutContext const& context,
        Size const& finalSize)
    {
        uint32_t itemCount = context.ItemCount();
        std::vector<double> columnHeights(ColumnCount(), 0.0);
        double columnWidth = finalSize.Width / ColumnCount();

        for (uint32_t i = 0; i < itemCount; ++i)
        {
            auto element = context.GetOrCreateElementAt(i);            
            auto desiredHeight = element.DesiredSize().Height;

            auto minColumn = std::min_element(columnHeights.begin(), columnHeights.end()) - columnHeights.begin();
            double x = minColumn * columnWidth;
            double y = columnHeights[minColumn];

            element.Arrange({ (float)x, (float)y, (float)columnWidth, (float)desiredHeight });
            columnHeights[minColumn] += desiredHeight + m_spacing;
        }

        double maxHeight = *std::max_element(columnHeights.begin(), columnHeights.end());
        return { finalSize.Width, (float)maxHeight };
    }
}
