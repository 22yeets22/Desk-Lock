# Desk-Lock
A cheap desk lock that unlocks with an NFC card.

## Overview

This project is a DIY desk locking system designed to keep important items secure using NFC authentication. An ESP32 reads an NFC card via a PN532 module and controls a servo motor that locks or unlocks the desk. A photoresistor is used to detect when the drawer is closed so it can automatically re-lock.

The system is designed with power efficiency in mind by minimizing NFC polling time and keeping components inactive when possible.

## Motivation
I wanted a secure way to lock my desk because I keep important items inside and my little brother cannot be trusted with it. Buying a commercial lock felt boring and expensive, so building one with NFC was more interesting and let me design my own NFC card and reader.


### PCB Design
![PCB Screenshot](nfccard/pcb.png)

### Wiring Diagram
![Wiring Diagram](wiringdiagram.png)
