# DK Bongos Arduino
This project contains Arduino code to make a microcontroller that emulates the DK Bongos controller by reporting inputs to the console through the Gamecube cable.

### Parts needed for the circuitry

- 1 Arduino UNO
- 2 Piezo disks
- 1 Microphone
- 1 Button
- 1 Gamecube cable
- 2 100 Ohm resistor
- 1 1k Ohm resistor
- 2 1M Ohm resistor
- 1 Logic level converter
- 1 Solderable protoboard (optional, you can just solder the cables directly but I prefer using a protoboard)
- Jumper wires

### Materials needed for the case (keep in mind that I used these to keep things cheap and accessible)

- 2 Plastic buckets
- 4 Silicon stretchable lids for the bongo membrane (they have to be smaller in diameter than the buckets)
- Hot glue
- Painter tape
- 1 Cardboard box

## Tutorial
First of all, you'll have to solder the connections like in this diagram. The semi-transparent colors represent wires underneath the protoboard.
<img width="1920" height="764" alt="pcb" src="https://github.com/user-attachments/assets/f324bb61-6231-4b16-9bfe-f85e6ee582ac" />
Keep in mind that the text inside the circuitry refers to connections that you should make with the Arduino board, for example, where "Arduino 5V" is, you should solder a cable that connects to the "5V" port of the Arduino.

After that, you should flash the debug program to your Arduino and test with the serial console if the board is reading the inputs of the button, disks and microphone correctly, after that you can configure the thresholds to your liking. 

**Keep in mind that the default thresholds may be too high for your components, if you don't see any logs, try  lowering the thresholds**.

After configuring the thresholds while debugging, you can now apply those thresholds to the real program and flash the board with it. 

---
**Before building the bongos, try connecting the circuit to your console to test it**.
---

Now you can start building the bongos, cut 1 hole in 1 bucket and 2 holes (one for the piezo and the other for the Gamecube cable) in the other bucket. Then pass the piezo disks and the Gamecube cable through the holes.

Attach the piezo disks to the silicone lids, I ended up using 2 lids for each disk because I couldn't find any way to glue them to the silicone rubber so I made a silicone lid sandwich having one disk between the lids.

After that, now you can hot glue the protoboard and Arduino to the box that should be between the buckets. Hot glue the microphone to be on top of the box and the start button facing the player.

**It is highly recommended to cut an opening to access the micro usb of the Arduino board in case that you need to make adjustments to the code.**

<img width="500" height="550" alt="fa0d0a13-d3e8-49d8-acbf-744ab95df1dc" src="https://github.com/user-attachments/assets/0a189d03-5430-4f07-836c-78e75b661154" />

<img width="500" height="550" alt="e02cd7cf-954e-4278-9ab2-de57c435b278" src="https://github.com/user-attachments/assets/d9f8a7ec-1031-45a2-97fd-4310a0e6b825" />



Now cover the DK Bongos with the painter tape to tightly join the buckets to the box. 

**THIS STEP SHOULD BE THE LAST ONE AND ONLY DO IT WHEN YOU ARE SURE THAT EVERYTHING WORKS.**
<img width="935" height="524" alt="681a9ef7-0792-4786-8613-29ff348306c3" src="https://github.com/user-attachments/assets/38b98c3f-3744-4ebc-a319-dc77386050c4" />


## Disclaimer
I only tested with an original Wii, it should work with Gamecube too though. 

Because of limitations, the code is only compatible with Donkey Kong Jungle Beat, to play Donkey Konga you may change it to your liking.

This code utilizes the Nicohood Library (https://github.com/NicoHood/Nintendo).
