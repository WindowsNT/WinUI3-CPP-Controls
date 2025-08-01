# WinUI3 C++ controls

From the WinUI3 Community Kit which is C# only I am porting some controls to C++. Including a Sample application that demonstrates them.
Currently, Resizer and StaggeredLayout are available.

## Resizer

A control to change a double property. 

1. Put the style to your generic.xaml in Themes\ (change the namespace)
2. Put Resizer h/cpp/idl to your project, changing the namespace

To your layout then:

```
<local:Resizer
	Minimum="100"
	Maximum="400"
	Orientation="Horizontal"
	Value="{x:Bind R1,Mode=TwoWay}"/>
```

This creates a horizontal splitter (Vertical is also supported) which modifies the double value R1. This value can then be used into another control:

```
<StackPanel Orientation="Horizontal">
	<TextBlock Width="{x:Bind R1,Mode=OneWay">Text 1</TextBlock>
	<local:Resizer Minimum="100" Maximum="100" Orientation="Vertical" Value="{x:Bind R1,Mode=TwoWay}" />
	<TextBlock >Text 2</TextBlock>
</StackPanel>
```

You can also use it on a grid to size the entire grid row or column by having the ColumnDefinition's Width bound to that variable.

For a full example, see [XAML Lab](https://github.com/WindowsNT/XAML-Lab/), direct link [here](https://www.turbo-play.com/update2/tu.php?p=f3cf159b-de75-4427-8fe0-81a7ae61d3fa&f=88887777-A932-7654-A2E5-DECB481E355D).


## StaggeredLayout

A panel  that arranges its children in a staggered grid layout, similar to a masonry layout.
Put the StaggeredLayout h/cpp/idl to your project, changing the namespace. No generic.xaml is needed for this control.

```
<ScrollViewer Grid.Row="1" Grid.Column="0">
    <ItemsRepeater VerticalAlignment="Stretch" x:Name="MyRepeater"  ItemsSource="{x:Bind TheItems,Mode=OneWay}">
        <ItemsRepeater.Layout>
            <local:StaggeredLayout ColumnCount="10"/>
        </ItemsRepeater.Layout>

        <ItemsRepeater.ItemTemplate>
            <DataTemplate x:DataType="local:Item">
                <Rectangle Fill="SteelBlue"
                        Width="50"
                            HorizontalAlignment="Stretch"
                        Height="{x:Bind Number1}"  Margin="1"/>
            </DataTemplate>
        </ItemsRepeater.ItemTemplate>
    </ItemsRepeater>
</ScrollViewer>
```

```
// Example data: 30 rectangles of random height
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
```