# Desk-Lock
A cheap desk lock that unlocks with an NFC card.

## Overview
This project is a DIY desk lock which keeps items in your desk secure by using a NFC reader. An ESP32 reads an NFC card via a PN532 module and controls a servo motor that locks or unlocks the desk. A photoresistor is used to detect when the drawer is closed so it can relock automatically.

## Motivation
I wanted a secure way to lock my desk because I keep important items inside and my little brother cannot be trusted with it. Buying a commercial lock felt boring and expensive, so building one with NFC was more interesting and let me design my own NFC card and reader.

## Parts List (Bill of Materials)
- 1x of [Photoresistor](https://www.aliexpress.us/item/3256805782399608.html), TYPE 5528, PRICE N/A 
- 1x of [10k Resistor](https://www.aliexpress.us/item/2251832766343175.html), TYPE 10K, PRICE N/A 
- 1x of [MG996R Servo](https://www.aliexpress.us/item/3256808293405785.html), TYPE N/A, PRICE N/A
- 1x of [AC to DC Power Supply](https://www.aliexpress.us/item/3256806901002886.html), TYPE US Plug/DC 5V/3A, PRICE N/A 
- 1x of [ESP32 Development Board](https://www.aliexpress.us/item/3256805767190776.html), TYPE 1PCS-CP2102 TYPE-C, PRICE N/A
- 1x of [PN532 NFC Module](https://www.aliexpress.us/item/3256806852006648.html), TYPE PN532, PRICE N/A

### NFC Card
| Schematic | PCB | 3D View |
|-----------|-----|---------|
| ![Schematic](NFC%20Card/images/schematic.png) | ![PCB](NFC%20Card/images/pcb.png) | ![3D](NFC%20Card/images/3d.png) |


## Wiring Diagram
![Wiring Diagram](wiringdiagram.png)
