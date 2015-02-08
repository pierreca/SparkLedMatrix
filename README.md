# SparkLedMatrix
Matrix of 16 8x8 LED Matrices (NFM-12883) driven from a spark core.

## Current status:
- [x] Code to make text scroll across multiple matrices seems to work with 2 matrices.
- [x] First version of the PCB works fine (silkscreen isn't great though)
- [ ] Clean PCB silk screen
- [ ] Order more PCB and build more matrices.
- [ ] Connect the current prototype to the Spark cloud
- [ ] Display messages sent to the device using the Spark cloud API

## Hardware
* [NFM-12883AS-11 LED Matrix](https://upverter.com/upn/b3a03be171307eb0/)
* [AS1100PL driver (MAX7219 drop-in replacement)](https://www.modmypi.com/as1100pl-led-driver)
* [Spark Core](http://www.spark.io)
* Custom PCB: [Upverter](https://upverter.com/pierreca/2dc3fadd41948de2/NFM-12883-Backpack/) - [OshPark](https://oshpark.com/shared_projects/Dkkxd2oF)

## Custom board
This is my first PCB built using Upverter and OshPark. It's exactly the size of an NFM-12883 LED Matrix, and has the LED matrix on one side, and the driver and passive components on the other, allowing to line-up horizontally and/or vertically  multiple LED matrices.

## Code
Currently the code is super basic and only scrolls a "Hello world" message across 2 LED Matrices hooked up to a spark core. the code is written so that adding more LED Matrices is really easy and amounts to just changing one value.

### Making the message scroll
The LedControl library found on spark.io is a port from the Arduino LedControl library and contains basic functions such as piloting each LED individually, displaying letters using a monospaced font (called cp437) and "tweening" letters meaning scrolling a letter out while the next scrolls in.

Since this was a little too basic to obtain a message scrolling on multiple adjacent LED matrices I wrote 2 additional functions that make text scroll across multiple matrices in 2 different ways: either using the default monospaced font (which will always amount to one letter per matrix) or that trims whitespace to make it more readable and waste less columns.

The code to trim the whitespace is super basic right now and doesn't account for whitespaces between words yet.

## Pictures
![Current prototype](/pictures/currentproto.jpg)
