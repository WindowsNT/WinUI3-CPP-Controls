# WinUI3 C++ controls

From the WinUI3 Community Kit which is C# only I am porting some controls to C++.

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

For a full example, see [XAML Lab](https://github.com/WindowsNT/XAML-Lab/).

