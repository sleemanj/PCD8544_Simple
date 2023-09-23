<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [PCD8544_Simple](#pcd8544_simple)
  - [About Nokia 5110 Displays](#about-nokia-5110-displays)
  - [Voltage](#voltage)
  - [Wiring](#wiring)
  - [Download, Install and Example](#download-install-and-example)
  - [Troubleshooting](#troubleshooting)
    - [Blank Display](#blank-display)
    - [Background sometimes darkens](#background-sometimes-darkens)
    - [Foreground sometimes fades](#foreground-sometimes-fades)
    - [Random behaviour (garbled display, random blocks...)](#random-behaviour-garbled-display-random-blocks)
  - [Full Class Reference](#full-class-reference)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

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

* Download: https://sparks.gogo.co.nz/PCD8544_Simple.zip
* Open the Arduino IDE (this library was tested in 1.6.9, but older versions should be fine too)
* Select the menu item Sketch > Import Library > Add Library
* Choose to install the PCD8544_Simple.zip file you downloaded
* Now you can choose File > Examples > PCD8544_Simple > 01_PrintText

Upload the example to your Arduino and admire the beauty of your display.  Try the other examples for more excitement and to learn how to control the display!  It's easy!


## Troubleshooting

### Blank Display

  1. Check your wiring.  Check that when the display should be displaying something that RST is close to 3.3v, and that CE is close to 0v (measured relative to Gnd of course).
  2. Adjust contrast - open the `File > Examples > PCD8544_Simple > A01_ContrastHelper` sketch, upload it, hopefully you will find a contrast level which suits.  You can then put `lcd.setContrast(xx);` right after your `lcd.begin()` in your actual sketch.
  3. Try pressing firmly in the center of the top metal section of the LCD.  Underneath this is the "zebra strip" which presses against the PCB contacts, sometimes these don't make a good connnection.  If pressing helps, press it firmly then bend the tabs over a bit to hold it in place.  
  4. Still no go, and you are sure your wiring is OK, remove the LCD from the PCB (use a thin screwdriver to straighten and push the tabs through the holes), once removed you will see the contact points on the PCB hwhich you can swab with a cotton bud dipped in a solvent like acetone or methylated spirits.  Looking at the back of the LCD you will see the "zebra strip", a short (about 1cm) strip of a (in the ones I have done, beige coloured) rubber type material, wipe that surface with your swab as well.  Reassemble, and when doing so press it firmly to the PCB when bending the tabs to ensure a good strong contact is made (I use a quick-clamp).
  
### Background sometimes darkens

  1. Contrast is probably too high, this will cause the off crystals to be "right on the edge" of turning on and it doesn't take a lot to tip them over the edge, creating that "darkening background" issue.
  
### Foreground sometimes fades

  1. Contrast is probably too low, this will cause the on crystals to be "right on the edge" of turning off and it doesn't take a lot to tip them over the edge, creating that "darkening foreground" issue.
  2. Zebra strip may need cleaning or display just need snugging up a bit.  See points 3 and 4 in the Blank Display section above.

### Random behaviour (garbled display, random blocks...)

  1. Zebra strip may need cleaning or display just need snugging up a bit.  See points 3 and 4 in the Blank Display section above.
  2. Your code might have a bug, are you running out of RAM perhaps, it doesn't take much.  Make sure your strings are F() wrapped where appropriate and possible.
  
  
## Full Class Reference

I recommend to just look at the examples which show you how to use all the features, but if you want the nitty-gritty then here is the [full class reference](https://rawgit.com/sleemanj/PCD8544_Simple/d2c5ae1/docs/html/class_p_c_d8544___simple.html)

Thanks to the super kind folks of [RawGit](https://rawgit.com/) and [MaxCDN](http://www.maxcdn.com/)
