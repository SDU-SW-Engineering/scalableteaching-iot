# Relay Module with 1 relay

## Module Description

This module is a board with 1 mechanical relay. The device needs constant power and ground other than just the signal voltage.\
To use the relay you need to supply a 5vdc signal on the control pin.\
The output of the relay has a normally opened (NO), a normally closed(NV) and a common(COM).\
When a relay is powered the NO contact closes the NC contact opens.\
The signal on both NC and NO comes from the COM terminal of the relay or is supplied from the common terminal.\

The input for the relay is galvanically isolated from the relay to ensure that switching the relay does not damage the mainboard.\

Inputs on pin header (left side on image)
- GND: Ground.
- IN1: Signal pin for the relay.
- VCC: 5v supply input.

Outputs on screw terminal (right side on image).\
- NO : Will be disconnected while the relay is unpowered.
- NC : Will be connected while the relay is unpowered.
- COM: Common

## Specsheet for the individual relays
[Relay - JQC-3FF-v1](../specsheets/jqc-3ff-v1.pdf)


### Device from control side
<img src="../pictures/1x-relay-module-1.png" alt="Picture describing the outputs and buttons of the device" title="Battery module 2pcs 18650 battery - Overview" style="max-width: 400px">

### Device from relay side
<img src="../pictures/1x-relay-module-2.png" alt="Picture describing the outputs and buttons of the device" title="Battery module 2pcs 18650 battery - Overview" style="max-width: 400px">

## Device Count
There are the following number of devices in the inventory: 5