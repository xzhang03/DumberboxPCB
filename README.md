# DumberboxPCB
 PCB port of arthur's dumberbox
 
 Arthur's repo (under dumberbox directory): https://github.com/asugden/bebox
 
## How to order
1. Use one of the PCB printing services (e.g., [JLCPCB](https://jlcpcb.com/), [PCBWAY](https://www.pcbway.com/), [OSHPARK](https://oshpark.com/), [etc](https://pcbshopper.com/)). Upload the zip Gerber files from [here](https://github.com/xzhang03/DumberboxPCB/tree/main/v1.2). The sizes are pre-set so just choose your quantity, color, etc... You are good to go with PCBs
2. Upload the [bill of materials excel files](https://github.com/xzhang03/DumberboxPCB/tree/main/v1.25) to [Digikey](https://www.digikey.com/en/mylists/). The quantities are for 1 unit. For resisters, trimmers, and header pins, you are better off using bulk kits from Amazon/Ebay. Please feel free to ask me about replacements.

> Please do not use headers for mounting the microcontroller on this board since I make use of the bottom pins. I'll fix it in a future version but for now please solder the microcontrollers directly on the PCB.

## Schematics
![Schematics](https://github.com/xzhang03/DumberboxPCB/blob/main/v1.25/Schematic_DumberboxPCB_2022-09-27.png)

## I2C pinout
I2c is used for communicating with the lick sensor and other peripherals. See [here](https://github.com/xzhang03/NidaqGUI/blob/master/PCBs/I2C_notes/readme.md) for I2c pinout

## Footprint
![Footprint](https://github.com/xzhang03/DumberboxPCB/blob/main/v1.25/board_footprint.png)

## Versions
v1.2 Fixed missing pulldown resistors and silk screen errors

v1.25 Changed mounting hold positions


