# Level Shifting Methods

There are of course many ways to shift voltage levels.  You only need to shift in one direction, from the Arduino to the Display. 

You need at a minimum 4 level shifted channels (as well as a 3v3 power source of course), the CE pin can be connected directly to ground (provided you only have this display on the SPI bus).

## Resistor Level Shifter

Experiments have shown that even simply a voltage-divider on each signal appears to be sufficient for level shifting this device as a bare minimum.  Shown here are a 330R and 620R combination (untested, actual tests conducted with 2.44k and 4.7k, which worked but seemed sensitive to electrical noise).

![Example Wiring Diagram using Resistor Level Shifter](https://rawgit.com/sleemanj/PCD8544_Simple/master/docs/wiring-diagram-resistor.png "Example Wiring Diagram using Resistors")

## Zener Diode Level Shifter

If you have some 3v3 Zener Diodes lying around, they can be used to accomplish the one-directional level shifting, as shown.

![Example Wiring Diagram using Zener Level Shifter](https://rawgit.com/sleemanj/PCD8544_Simple/master/docs/wiring-diagram-zener.png "Example Wiring Diagram using Zener Diodes")

## "4050" Level Shifter

Another common way to accomplish one-directional level shifting such as required here is using a [CD4050BE Non Inverting Hex Buffer IC](http://sparks.gogo.co.nz/5-of-CD4050BE-DIP-Hex-Non-Inverting-Buffer-IC-348.html).

Note below that a 100nF Capacitor (ceramic) is placed across the CD4050's Power and Ground, that the 4050 is powered from the 3.3V Supply (this is what makes it level shift for you), and again we have a 100K Resistor pulling RST down until it's driven by the Arduino.  

Note also that the unused inputs on the CD4050 are connected to 3v3, in accordance with the datasheet (it is common on logic chips to "tie" unused inputs to either Vcc or Ground, otherwise they may oscillate uncontrollably and cause the chip to be damaged).

![Example Wiring Diagram using CD4050 Level Shifter](https://rawgit.com/sleemanj/PCD8544_Simple/master/docs/wiring-diagram-4050.png "Example Wiring Diagram using CD4050 Level Shifter")
