# PCD8544_Simple
Simple Arduino library for Nokia 5110 type displays.

## About Nokia 5110 Displays

The Nokia 5110 Display is an 84 pixel by 48 pixel monochrome graphic LCD display.  

The display was used in Nokia mobile phones, and has become highly popular amongst hobby electronics because of it's relative abundancy, cheap price, and simplicity to use.

## Voltage

Modules coming out of China commonly are marked as "3-5v".  This is by most accounts incorrect and these devices should be used only at 3.3v

**You should consider the display as a 3v3 display only**, do not feed it 5v signalling, and **absolutely do not put 5v on Vcc** if you are using a 5v Arduino, you need to level-shift.

## Wiring

Depicted here is the general wiring required.  As mentioned above if you are using a 5v Arduino you MUST level shift, there are many ways to accomplish the level shifting so it's shown here as a "black box" insert your specific type of level shifting arrangement as necessary (or use a 3.3v Arduino).

![Example Wiring Diagram](https://rawgit.com/sleemanj/PCD8544_Simple/master/docs/wiring-diagram.png "Example Wiring Diagram")

## Level Shifting Ideas

The most common way to accomplish one-directional level shifting such as required here is using the venerable [CD4050BE Non Inverting Hex Buffer IC](http://sparks.gogo.co.nz/5-of-CD4050BE-DIP-Hex-Non-Inverting-Buffer-IC-348.html)


![Example Wiring Diagram using CD4050 Level Shifter](https://rawgit.com/sleemanj/PCD8544_Simple/master/docs/wiring-diagram-4050.png "Example Wiring Diagram using CD4050 Level Shifter")
