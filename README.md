# PCD8544_Simple
Simple Arduino library for Nokia 5110 type displays.

## About Nokia 5110 Displays

The Nokia 5110 Display is an 84 pixel by 48 pixel monochrome graphic LCD display.  

The display was used in Nokia mobile phones, and has become highly popular amongst hobby electronics because of it's relative abundancy, cheap price, and simplicity to use.

## Voltage

Modules coming out of China commonly are marked as "3-5v".  There are varying accounts of people's devices failing when being powered from 5v.

**You should consider the display as a 3v3 display only**, do not feed it 5v signalling, and **absolutely do not put 5v on Vcc** if you are using a 5v Arduino, you need to level-shift.

## Wiring

Depicted here is the general wiring required.  As mentioned above if you are using a 5v Arduino you MUST level shift, there are many ways to accomplish the level shifting so it's shown here as a "black box" insert your specific type of level shifting arrangement as necessary (or use a 3.3v Arduino).

Notice that there is a 100KΩ Resistor shown "pulling down" the RST pin, this ensures that the display is "held in reset" until such time as the code enables it, this is good practice, although maybe you can get away without it.

Notice that there is a 330Ω Resistor shown on the BL (Backlight) pin, you can adjust this resistor (or use a potentiometer, or connected it to a PWM pin of your arduino or ...) as desired to get whatever backlight brightness you want (or not connect it at all to turn it off).

![Example Wiring Diagram](https://rawgit.com/sleemanj/PCD8544_Simple/master/docs/wiring-diagram.png "Example Wiring Diagram")

## Level Shifting

There are of course many ways to shift voltage levels.  You only need to shift in one direction, from the Arduino to the Display. 

You need at a minimum 4 level shifted channels (as well as a 3v3 power source of course), the CE pin can be connected directly to ground (provided you only have this display on the SPI bus).

### Zener Diodes Level Shifter

If you have some 3v3 Zener Diodes lying around, they can be used to accomplish the one-directional level shifting, as shown.

![Example Wiring Diagram using Zener Level Shifter](https://rawgit.com/sleemanj/PCD8544_Simple/master/docs/wiring-diagram-zener.png "Example Wiring Diagram using Zener Diodes")

### "4050" Level Shifter

Another common way to accomplish one-directional level shifting such as required here is using a [CD4050BE Non Inverting Hex Buffer IC](http://sparks.gogo.co.nz/5-of-CD4050BE-DIP-Hex-Non-Inverting-Buffer-IC-348.html).

Note below that a 100nF Capacitor (ceramic) is placed across the CD4050's Power and Ground, that the 4050 is powered from the 3.3V Supply (this is what makes it level shift for you), and again we have a 100K Resistor pulling RST down until it's driven by the Arduino.  

Note also that the unused inputs on the CD4050 are connected to 3v3, in accordance with the datasheet (it is common on logic chips to "tie" unused inputs to either Vcc or Ground, otherwise they may oscillate uncontrollably and cause the chip to be damaged).

![Example Wiring Diagram using CD4050 Level Shifter](https://rawgit.com/sleemanj/PCD8544_Simple/master/docs/wiring-diagram-4050.png "Example Wiring Diagram using CD4050 Level Shifter")


## Download, Install and Example

* Download: http://sparks.gogo.co.nz/PCD8544_Simple.zip
* Open the Arduino IDE (this library was tested in 1.6.9, but older versions should be fine too)
* Select the menu item Sketch > Import Library > Add Library
* Choose to install the PCD8544_Simple.zip file you downloaded
* Now you can choose File > Examples > PCD8544_Simple > 01_PrintText

Upload the example to your Arduino and admire the beauty of your display.  Try the other examples for more excitement and to learn how to control the display!  It's easy!

## Full Class Reference

I recommend to just look at the examples which show you how to use all the features, but if you want the nitty-gritty then here is the [full class reference](https://rawgit.com/sleemanj/PCD8544_Simple/70b4c90/docs/html/class_p_c_d8544___simple.html)

Thanks to the super kind folks of [RawGit](https://rawgit.com/) and [MaxCDN](http://www.maxcdn.com/)