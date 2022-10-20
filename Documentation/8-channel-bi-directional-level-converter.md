# 8 Channel level converter

## Module Description 
This device will convert logic signals from a voltage range of 1.2-3.6v to a range of 1.65-5.5v.\
The device has 8 channes which will independently convert the signal.\
The output of the A ports are supplied with the voltage from VA and the output of the B ports are supplied with the voltage from VB.\
The relationship between the voltage sources should allways be VA ≤ VB.\
To enable the output you need to give signal high on the Output Enable pin(OE). The voltage range for Signal high on OE is VA*0.65-5.5v

The output of the device will follow the input signal and it will be equal to the suplly voltage for that side (VA or VB)

It is important that the ground is shared between the two sides of the device.

## Pinout
- VA: Supply voltage for output on A ports.
- VB: Supply voltage for output on B ports.
- OE: Output enable pin.
- A1-A8: Input/Output pins for lov voltage(1.2-3.6v) ports.
- B1-B8: Input/Output pins for high voltage(1.65-5.5v) ports.
- GND: Shared Ground.

## Specsheet for the chip
[Level shifting chip](../Specsheets/TXS0108E-etcTI.pdf)


### Device from control side
<img src="../Pictures/8-channel-bi-directional-level-converter.png" alt="Picture describing the outputs and buttons of the device" title="Battery module 2pcs 18650 battery - Overview" style="max-width: 400px">

## Device Count
There are the following number of devices in the inventory: 10