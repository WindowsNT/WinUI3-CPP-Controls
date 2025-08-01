#pragma once

#include "MainWindow.g.h"
#include "Item.h"

inline std::random_device rd;
inline std::mt19937 gen(rd());



namespace winrt::Sample::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }


        double _V1 = 0;
        double V1()
        {
            return _V1;
		}
        void V1(double value)
        {
            if (_V1 != value)
            {
                _V1 = value;
                m_propertyChanged(*this, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"V1"));
                m_propertyChanged(*this, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"VV1"));
            }
        }
        double _X1 = 0;

        // Example data: rectangles of random height
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Sample::Item> items =
            winrt::single_threaded_observable_vector<winrt::Sample::Item>();
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Sample::Item> TheItems()
        {
            items.Clear();
            
            for (int i = 0; i < 30; ++i)
            {
				int height = std::uniform_int_distribution  <int>(10, 50)(gen);
                winrt::Sample::Item item;
                item.Number1((double)height);
                items.Append(item);
            }
            return items;
        }

        Microsoft::UI::Xaml::GridLength VV1()
        {
            // Default is "Star"
            if (_V1 == 0)
                return Microsoft::UI::Xaml::GridLength{ 1, Microsoft::UI::Xaml::GridUnitType::Star };
            else
            {
                // Get actual length first
                auto top = Content();
                auto grid = top.as<Microsoft::UI::Xaml::Controls::Panel>().FindName(L"Grid1").as<Microsoft::UI::Xaml::Controls::Grid>();
                if (!grid)
                    return Microsoft::UI::Xaml::GridLength{ 1, Microsoft::UI::Xaml::GridUnitType::Star };

                // Get col 1 actual width
                if (_X1 == 0)
                {
                    auto row = grid.ColumnDefinitions().GetAt(0);
                    auto aw = row.ActualWidth();
                    if (aw == 0)
                        return Microsoft::UI::Xaml::GridLength{ 1, Microsoft::UI::Xaml::GridUnitType::Star };
                    _X1 = aw;
                }

                return Microsoft::UI::Xaml::GridLength{ _X1 + _V1, Microsoft::UI::Xaml::GridUnitType::Pixel };

            }
        }

        void OnRangeChanged(Sample::RangeSelect rs , IInspectable)
        {

            [[maybe_unused]] double start = rs.StartValue();
            [[maybe_unused]] double end = rs.EndValue();

        }


        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
        {
            return m_propertyChanged.add(handler);
        }
        void PropertyChanged(winrt::event_token const& token) noexcept
        {
            m_propertyChanged.remove(token);
        }
		winrt::event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}

namespace winrt::Sample::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
