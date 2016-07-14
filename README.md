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

:bulb: [Some actual level shifting methods are described here.](LEVELSHIFT.md) :bulb: 

Notice that there is a 100KΩ Resistor shown "pulling down" the RST pin, this ensures that the display is "held in reset" until such time as the code enables it, this is good practice, although maybe you can get away without it.

Notice that there is a 330Ω Resistor shown on the BL (Backlight) pin, you can adjust this resistor (or use a potentiometer, or connected it to a PWM pin of your arduino or ...) as desired to get whatever backlight brightness you want (or not connect it at all to turn it off).

![Example Wiring Diagram](https://rawgit.com/sleemanj/PCD8544_Simple/master/docs/wiring-diagram.png "Example Wiring Diagram")

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