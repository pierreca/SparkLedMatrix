The end goal of this project is to build a Matrix of 16 8x8 LED Matrices (NFM-12883) driven from a spark core that can be used to display... stuff :grin:

## Current status:
- [x] Code to make text scroll across multiple matrices seems to work with 2 matrices.
- [x] First version of the PCB works fine (silkscreen isn't great though)
- [x] Connect the current prototype to the Spark cloud
- [x] Display messages sent to the device using the Spark cloud API
- [x] Clean PCB silk screen
- [x] Order more PCBs
- [x] Build more Matrices
- [x] Build and order a "motherboard" on which LED matrix modules will be connected.
- [x] Test the "motherboard".
- [x] Cleanup code style.
- [ ] Implement "Line" abstraction layer that will allow to update and render both lines independently

## Hardware
* [NFM-12883AS-11 LED Matrix](https://upverter.com/upn/b3a03be171307eb0/)
* [AS1100PL driver (MAX7219 drop-in replacement)](https://www.modmypi.com/as1100pl-led-driver)
* [Spark Core](http://www.spark.io)
* Custom Backpack PCB [Upverter](https://upverter.com/pierreca/2dc3fadd41948de2/NFM-12883-Backpack/) - [OshPark](https://oshpark.com/shared_projects/Awyc02gR)
* Custom Motherboard PCB [Upverter](https://upverter.com/pierreca/2f7e1367325db8bc/Spark-LED-Matrix-Motherboard-2/) - [Oshpark] (https://oshpark.com/shared_projects/4Sw3dNy7)

## Custom PCB
The backpack is my first PCB built using Upverter and OshPark. It's exactly the size of an NFM-12883 LED Matrix, and has the LED matrix on one side, and the driver and passive components on the other, allowing to line-up horizontally and/or vertically  multiple LED matrices.

The motherboard is my second PCB, also built using Upverter and OshPark. it fits 2 lines of 8 matrices each.

## Code
Currently the code is super basic and just scrolls or displays statically a message received from a Spark Cloud API across LED Matrices hooked up to a spark core. the code is written so that adding more LED Matrices is really easy and amounts to just changing one value.

### Making the message scroll
The LedControl library found on spark.io is a port from the Arduino LedControl library and contains basic functions such as piloting each LED individually, displaying letters using a monospaced font (called cp437) and "tweening" letters meaning scrolling a letter out while the next scrolls in.

Since this was a little too basic to obtain a message scrolling on multiple adjacent LED matrices I wrote additional functions that make text scroll across multiple matrices in 2 different ways: either using the default monospaced font (which will always amount to one letter per matrix) or that trims whitespace to make it more readable and waste less columns. I've also added a method to simply statically display text on multiple matrices (trimming spaces).

## Pictures
![Current prototype](/pictures/currentproto.jpg)
![Current prototype](/pictures/parts.jpg)
![Current prototype](/pictures/matrices_assembly.jpg)
![Current prototype](/pictures/matrices_back.jpg)
![Current prototype](/pictures/matrices_front.jpg)
