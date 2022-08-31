 ### THIS PROJECT WAS MY FIRST DEVICE...AND IT'S OUTDATED...NOW I AM INTERESTED IN ANOTHER MIDI PROJECTS.

The first device it's not probably the best so i have discontinued this project a long time ago.

You can see every MIDI devices i have built, in my principal web-page or here, in my github repositories.

Both sites, github and the web, contains everything about my MIDI devices, you can watch or download all files on both sites. 

Here it's the web :

https://srmorrris.github.io/AH-HI-MAHI-WEB-OS-/

But i can show you this first device i have made, with an arduinoMEGA 2560.

Firstly, i was started with Arduino UNO, but the project growed, and growed.. gettin' bigger and bigger..
and i was pushed to use a bigger board, an arduino MEGA.

If you want to use an Arduino UNO you will need to change some pins on the code, in order to get a succesful compilation in Arduino IDE (because arduino mega has got much more pins than UNO).

This it´s the pedal-board i have built with this code:

![172305_281f032dea (1)](https://user-images.githubusercontent.com/80991642/187542973-35e040d8-80a5-49ad-86f4-9be6574cfdbf.jpg)

And the next days the project moved to one USB-MIDI-controller-desktop-device (pots, encoder and some small buttons). 
I have made so many changes in my first device :D

![680718cacd2fbae552cdfb9eaa7da-2677791](https://user-images.githubusercontent.com/80991642/187591438-45e6adf0-d294-4c52-b88d-f2eb27e02741.jpg)

But, in these days.., finally i find the Ignotus666 Midi controller and my project goes to OFF..

https://github.com/ignotus666/Bluetooth-Pedalboard

https://github.com/ignotus666/desktop-midi-controller

Watch the next video and you will see the little improvement, and why i have decided to retire from my first project..  Ignotus666 controller it's simply awesome!! (ws2812rgb, ili9341, etc..) (i will show you how i have made mine..don't worry..).

[![Alt text](https://img.youtube.com/vi/EoB76IpAQk8/0.jpg)](https://www.youtube.com/watch?v=EoB76IpAQk8)


 # Arduino-USB-MIDI-Pedalboard


You can build your Pedal-board with Arduino MEGA for use it in your DAW's (cubase,etc..) or VST plugins (like amplitube,guitar rig,etc..). 
Controlling all parameters via MIDI.

You can use whatever Arduino board you want..

If you use a MEGA or UNO, this boards needs to be flashed, in the Atmel8u2 or the Atmel16u2 chip, in order to get the USB-MIDI comunication. 

![atmelchips](https://user-images.githubusercontent.com/80991642/187557061-b7158547-1eda-429c-af1a-1262c93e5ed6.jpg)

Be aware that certain kind of boards can't be flashed..like the CH340G boards.., in this cases you will need another pc-programs in order to get the MIDI comunication (this programs are hairless, loopbe1, midiyoke, etc..).


This MEGA board can be flashed into HIDUINO 
(The arduino mega and uno from the picture before, can be flashed too):


![GOOD_ONE specialone](https://user-images.githubusercontent.com/80991642/187542768-761e2a9a-888d-495d-858f-04d92f0e5002.jpg)


Maybe you can't watch it in this pictures , because it's a very small chip, it's near to the usb-female conector, but there it's a very small chip and one ICSP port, attached to this chip.


This MEGA board can't be flashed into HIDUINO (CH340G chip, here there's no atmel16u2 usb-chip):

![bad one horror inferno](https://user-images.githubusercontent.com/80991642/187542835-87f0bee2-9d14-4733-a547-2bef17d00b21.jpg)

This it's the wrong one (for hiduino), there it's a "quartz crystal 12 mhz" next to the CH340G chip.. maybe the atmel 2560 chip it's a good one.. but this board can't be flashed into hiduino...you will need another  pc-programs (like hairless,loopbe1, midi-yoke, etc..) in order to get usb-midi-comunication and everything will works fine in your DAW or plugin.

If you use other boards like LEONARDO OR TEENSY, ESP32, etc.. you will only need to upload one sketch for achieve the USB-MIDI comunication. 
(You have only to add one line or include a library into your sketch).

Or maybe you prefer to build your own arduino board , with atmel 328 or 1284 chips, etc..


 ## Materials Pedalboard:

 
- Arduino MEGA 2560 board. 
  
- One switch SPST (2pin) (ON/OFF): you can use one more switch, +5V USB for ON/OFF the device if you want..

![41Xfrd3VpWL _AC_SY355_](https://user-images.githubusercontent.com/80991642/187557725-ca4ee3d6-ff5c-49f3-8abe-6461d8935a19.jpg)

  This switch it's used to change the arduino-mode: "arduino usb-serial comunication" or the "hiduino usb-midi comunication". 

  The switch it's connected to 2 pins in the arduino board (the atmel16u2 ICSP) (see the bottom of this page, how to achieve usb-midi comunication). 

  SWITCH ON----Hiduino usb-midi comunication.

  SWITCH OFF---Arduino usb-serial comunication.

- 23 Buttons (momentary buttons, Normally open):

  11 buttons will be used for foot-switching, other buttons are small micro-switches for turning ON/OFF some other features on each pedal.
  
  I have used some small and cheap micro foot switches and arcade buttons for foot-switches and micro-small buttons for the other stuff. You can use whatever momentary button you want.., but with normally closed.. you will need to change some lines in the sketch.
	
- 2 multiplexers cd74hc4067: 

![MULTIPLEXOR](https://user-images.githubusercontent.com/80991642/187559132-0e077a11-f252-428f-9763-c7b7880a0eec.jpg)


- 16 Linear potentiometers 10k:

![41Q1lTVhGnL](https://user-images.githubusercontent.com/80991642/187558812-f31d6e01-e0d3-437d-837a-ac8aabf636e3.jpg)


- 24 220 ohms resistors for the leds.
	
![51OYaMHj+ZL _AC_SL1100_](https://user-images.githubusercontent.com/80991642/187599796-4f066efd-ca61-4880-b24c-4691fb99ecd3.jpg)

- 16 RGB leds (cathode common). 

![RGB LED](https://user-images.githubusercontent.com/80991642/187558454-0fbac7f9-6cd7-4060-8362-ea37b885d07a.jpg)

    NOTE: but you can use whatever led-model you want,  better... the cheapest one... but you must think that you will need more than 16 RGB leds.. with single coloured leds you will need more than 24 leds...

    2 banks with 8 positions each bank, gives 16 leds, and plus... 8 pedal switches, the "just in time" ones... Total=24 leds , with the rgb leds you will only need 8 leds, but each led its RGB, so each led got 4 pins...gives you 8x4=32 outputs from mux..

- 1 lcd screen (I2C 20x04) 4PINS: +5V; GND; SCK; SDA. (you can choose blue or green)

![LCD2004-I2C-Blue-Operation](https://user-images.githubusercontent.com/80991642/187595881-aae10ea1-50a0-4f1a-b6c8-eb3df727c334.jpg)

 ## Let's.. build your pedalboard...
							  
- First, you have to install Arduino IDE and the required libraries for arduino IDE. 
(Control.Surface, encoder, etc.., you will see detailed instructions for install required libraries in my files).

- Install Hiduino firmware (in order to get usb-midi communication). 
(see youtube video at the bottom of this chapter, how to install hiduino)

(REMember: ARDUINO UNO or MEGA boards needs to be flashed in order to get USB-MIDI comunication).

Or you can use another way to get usb-MIDI comunication using programs in your pc, like hairless, or loopbe1, etc... 

    NOTE: Arduino uses usb-serial comunication (CH340G boards are not the best ones for MIDI..i think..), but you will need the usb-MIDI comunication with your DAW or plugin.
    So you can use other pc-programs like hairless,loopbe1,midi-yoke, etc.. for the usb-MIDI comunication, but i have prefer the hiduino firmware (pimp my moco lufa, or usb midiklik).
    Hiduino brings you the native USB-MIDI comunication (REMember: teensy or leonardo, etc.. only needs to upload an sketch).
    So you connect your usb and the device will be recognized as an USB-Midi device.
    When your arduino it's on usb-Midi comunication mode , you can´t upload sketches to your arduino (you will need to come-back to serial-usb comunication for being allow to upload sketches).
    People uses "atmel flip" for the flashing-proccess into hiduino and then reflash into arduino for upload sketches.
    But you can implement a switch for change into hiduino or arduino state (midi or serial) (see tutorials about hiduino or pimpmymocolufa, usb midiklik etc..). You don´t need Atmel Flip anymore after installation.   

  I have followed this video in order to get the hiduino/arduino switch. And the USB-MIDI Comunication:
  Press play.. if you don't understand spanish you can search for another tutorials (usb midiklik, pimpmymocolufa, hiduino, etc..)


[![Alt text](https://img.youtube.com/vi/ITJnWoss8xE/0.jpg)](https://www.youtube.com/watch?v=ITJnWoss8xE)


-Upload the sketch "Usb_MIDI_Pedal_board Arduino.ino" included in my files, into your arduino. And That´s it!!. 

FINISHED!!

 ## How it works..


-Using CD74HC4067 multiplexers for having more analog and digital outputs in the arduino board...

Gives more analog potentiometers and more digital buttons.
(but you can skip this option if you are happy with the amount of your digital/analog outputs in your arduino). 
(In the code, one multiplexer named mux2 it's for 16 digital outputs and the other multiplexer , named mux3, it's for 16 analog outputs).

-I have used 16 analog potentiometers and 23 digital buttons in my pedalboard.

![5device](https://user-images.githubusercontent.com/80991642/187542120-98b99f54-b492-4334-b6bf-820c780a9d51.jpg)

![4device](https://user-images.githubusercontent.com/80991642/187542100-68c962b5-17a8-4d62-9e4d-8299dec1d4be.jpg)

(you can use whatever amount you want.. but i recommend 15 buttons and 8 potentiometers, at least).

-Using 8 leds and 8 momentary push button for JUST IN TIME Pedals. 

![1device](https://user-images.githubusercontent.com/80991642/187542012-1ccc2f19-bc21-490f-85e6-e05d2184799f.jpg)

The leds are showing the pedal-state, if the pedal it's on or off.
(8 pedals are available for control ON/OFF JUST IN TIME!!)

So you push the micro foot-switch button and the pedal goes to ON and the led turns on the green-light.
And you push it , once more... and the pedal goes to OFF and the led goes to OFF too.
So this 8 buttons and their 8 leds reflects the real pedal-state on/off ALWAYS!!.

## Let's use the pedalboard in a DAW

So you open a MIDI track in your DAW or execute standalone plugin and you can (right click) "Midi learn" every potentiometer or parameter on the vst-plugin screen.

Moving potentiometer or pressing the button, the action will be recorded.
You must select "All midi inputs" in the midi track.
And select your vstplugin at midi output , please be sure to enable monitor in this midi track and the midi track it's selected (left click mouse and track it's selected) (see arrow 1 in picture) when you use the midi controller..., in order to get everything working fine, this happens with every midi controller on market...


![Sin nombre](https://user-images.githubusercontent.com/80991642/187542268-78b4f9dd-88c4-4e97-b26e-4ea88f854065.jpg)

-Using the other leds (8 leds more..) for showing the bank position.(4 leds are for showing the bank-amp position, and the other 4 leds, are for showing the bank-pedal position).

Bank positions 1-4 are green led coloured, and bank positions 5-8 are blue led coloured on both banks.

-2 banks (named bank-amp and bankpedal). 8 different positions on each bank:


** - Bank-pedal= 8 pedals available and 4 potentiometers on each pedal 
You will use two buttons on BANKPEDAL.. one button it's for increment and the other one button it's for decrement the bank position on bank-pedal.(see picture, the 2 black buttons)
(8 pedals and 4 pots each pedal) 

And here you have another extra button, the red one button, it's for turn ON/OFF the pedal effect .


** - Bank-amp= 8 different positions for control amps or racks, etc. 4 potentiometers available on each bank.
You will use two buttons on BANKAMP... one button it's for increment and the other one it's one for decrement the bank position on bank-amp.
(8 amps or racks and 4 pots each amp or rack).

Please, notice in the pedalboard picture there are more potentiometers than in the code (4 potentiometer works better than 8..especially for the people).


*Using i2c lcd screen for showing 8 potentiometers graph-bars , the screen shows the volume bar for 8 potentiometer.


![3device](https://user-images.githubusercontent.com/80991642/187542077-d602aafd-43f5-4f59-9d5e-d002f30b28cf.jpg)

![2device](https://user-images.githubusercontent.com/80991642/187542061-6044089b-30f7-493f-b288-5b356f972b97.jpg)


This project was discontinued, I was hard-working this filess...one month updating , and learning, but now it's outdated and will not be more updated.

Finally i have achieved 16 volume bars for each potentiometer (16 graph-bars on screen )..and one volume/wah pedal.. and one encoder... but i have quited because i have found some other MIDI projects so much better than this one...
  
![pedalera back](https://user-images.githubusercontent.com/80991642/187543544-62a97346-4f9f-42f3-86be-04f425defb05.png)

![pedalboardhacendado](https://user-images.githubusercontent.com/80991642/187541490-b38e380f-eecb-4de5-9181-6b7aaf9b300b.jpg)

I was thinking to divide devices, pots and foot-switches, not a bad idea..

![2dc7787f8098cd69c440e345d286b-2677791](https://user-images.githubusercontent.com/80991642/187540049-8d2fd769-ba69-47c0-8ea9-492ced96c1d9.jpg)

![52be84827d9d241a82dc9d05445f2-2677791](https://user-images.githubusercontent.com/80991642/187540708-b34fd662-c5eb-41f5-a447-045990b67094.jpg)

![89acd46afb6c2fd5948952da73e4c-2677791](https://user-images.githubusercontent.com/80991642/187541009-99392831-707b-442f-98e2-9918aeae2875.jpg)

![81ab08539c8457d08e19ecc0a1996-2677791](https://user-images.githubusercontent.com/80991642/187540957-288d2454-f7fc-4b7b-b70f-db394c749a85.jpg)


## THIS PROJECT WAS MY FIRST DEVICE...HAS BEEN OUTDATED BY ANOTHER USB-MIDI PROJECTS. 

  Discussions, problems or recomendations will be attended

  ELIAS BARBERO CANO. 30 August 2022. Aragón. Open source.
