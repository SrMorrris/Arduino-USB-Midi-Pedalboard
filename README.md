 ### THIS PROJECT WAS MY FIRST DEVICE...AND IT'S OUTDATED...NOW I AM INTERESTED ON ANOTHER MIDI PROJECTS.

The first device you built, probably it´s not the best..so i have discontinued this project long time ago...

You can see all my other MIDI devices in my principal web-page or here, in my github repositories.
(both sites, github and the web, contains everything about my MIDI devices, you can watch or download all files on both sites).Here it's the web :

https://srmorrris.github.io/AH-HI-MAHI-WEB-OS-/

But now, i can show you my first device, built with an arduinoMEGA 2560.

Firstly, i was started with Arduino UNO, but the project growed, and growed.. gettin' bigger and bigger..
and i was pushed to use a bigger board, an arduino MEGA.

If you want to use an Arduino UNO you will need to change some pins on the code, in order to get a succesful compilation in Arduino IDE (because arduino mega has got much more pins than UNO).

![172305_281f032dea (1)](https://user-images.githubusercontent.com/80991642/187542973-35e040d8-80a5-49ad-86f4-9be6574cfdbf.jpg)

![680718cacd2fbae552cdfb9eaa7da-2677791](https://user-images.githubusercontent.com/80991642/187543032-5acd9038-b861-49cf-99ee-eb981184a066.jpg)

 # Arduino-USB-MIDI-footswitch


Build a Pedal-board with Arduino MEGA for use it in your DAW's (cubase,etc..) or VST plugins (like amplitube,guitar rig,etc..).

You can use whatever Arduino board you want..

If you use a MEGA or UNO, the board needs to be flashed, in the Atmega8u2 or the Atmega16u2 chip in order to get USB-MIDI comunication. 

Be aware that certain boards can't be flashed..like the CH340G boards.., in this cases you will need another pc-programs in order to get the MIDI comunication (this programs are hairless, loopbe1, midiyoke, etc..).

Watch this..


This MEGA board can be flashed into HIDUINO:


![GOOD_ONE specialone](https://user-images.githubusercontent.com/80991642/187542768-761e2a9a-888d-495d-858f-04d92f0e5002.jpg)


Maybe you can't watch it in this picture (it's very small, it's next to usb female conector), but there´s a very tiny chip named at16u2 and one ICSP port, attached to this chip.



This MEGA board can't be flashed into HIDUINO (CH340Gchip, there's no atmel16u2 usb-chip):

![bad one horror inferno](https://user-images.githubusercontent.com/80991642/187542835-87f0bee2-9d14-4733-a547-2bef17d00b21.jpg)

You can notice, in the last picture, the wrong one, there's a "quartz crystal 12 mhz" nearest the CH340G chip.. maybe the atmel 2560 chip it's a good one.. but this board can't be flashed...you will need another  pc-programs (like hairless,loopbe1, midi-yoke, etc..) in order to get midi-comunication and everything will works fine in your DAW or plugin.

If you use LEONARDO OR TEENSY, ESP32, etc.. you will only need to upload one sketch for achieve the MIDI comunication (only adding one line into your sketch).

You can build your own arduino board , with atmel 328 or 1284 chips, etc..


 ## Materials Pedalboard:

 
-*Arduino MEGA 2560 board. 
  
-*One switch SPST (2pin)(ON/OFF): 

  This switch it's for change into arduino usb-serial comunication or the hiduino usb-midi comunication . 
  The switch ON/OFF it's connected to 2 pins in the arduino board (the atmel16u2 ICSP). 

  ON----Hiduino usb-midi comunication.

  OFF---Arduino usb-serial comunication.

-*23 Buttons (momentary buttons Normally open):

  11 buttons will be used for foot-switching) (other buttons are small micro-switches for turn ON/OFF some other features on each pedal.
  
  I have used some small and cheap micro foot switches and arcade buttons for foot-switches and micro-small buttons for the other stuff. You can use whatever momentary button you want.., but with normally closed.. you will need to change the sketch.
	
-*2 multiplexers cd74hc4067.  : (the muxes gives more digital or analog outputs for the arduino)
	
-*16 Linear potentiometers 10k.

-*24 220 ohms resistors for the leds.
	
-*16 RGB leds (cathode common). 

   NOTE: but you can use whatever led-model you want, the better... the cheapest one... but you must think that you will need more than 16 RGB leds.. with single coloured leds you will need 24 leds...

   2 banks with 8 positions each bank, gives 16 leds, and plus... 8 pedal switches, the "just in momento" ones... Total=24 leds , with the rgb leds you will only need 8 leds, but each led its RGB, so each led got 4 pins...8x4=32..

-*1 lcd screen (I2C 20x04) 4PINS:+5V;GND;SCK;SDA. 

 
 # How to.. build your pedalboard...
							  
-Firstly, yOU HAVE TO Install the required libraries for arduino IDE.  (Control.Surface, encoder,etc.. you will see instructions for install the libraries in my file).

-Install Hiduino firmware (in order to get usb-midi communication). 

(REM: ARDUINO UNO or MEGA needs to be flashed into USB-MIDI).

Or you can use another way to get usb-MIDI comunication using programs like hairless, or loopbe1, etc... 

    NOTE: Arduino uses usb-serial comunication (CH340G are not the best ones for MIDI..i think..), but you    will need the usb-MIDI comunication.  (you need to comunicate with your DAW or plugin).
    So you can use other pc-programs like hairless,loopbe1,midi-yoke, etc.. for usb-MIDI comunication, but i have prefer the hiduino firmware (pimp my moco lufa, or usb midiklik).
    Hiduino brings the native USB-MIDI comunication (REM: teensy or leonardo, etc.. only needs to upload an sketch).
    So you connect your usb and the device will be recognized as an USB-Midi device.
    When your arduino it's usb-Midi comunication mode , you will be notice that you can´t upload sketches to your arduino (you will need to come-back to serial-usb comunication for being allow to upload sketches).
    People uses "atmel flip" for the flashing-proccess into hiduino and then reflash into arduino for upload sketches.
    But you can implement a switch for change into hiduino or arduino state (midi or serial) (see tutorials about hiduino or pimpmymocolufa, etc..).You don´t need Atmel Flip anymore after installation.   

  I have followed this video in order to get the hiduino/arduino switch.And the USB-MIDI Comunication

  https://www.youtube.com/watch?v=ITJnWoss8xE&ab_channel=DanielMarcial


-Upload the sketch "Usb_MIDI_Pedal_board Arduino.ino" into your arduino. That´s it.FINISHED!!

 # How it works..


-Using multiplexers for more analog and digital outputs in the arduino...

Gives more analog potentiometers and more digital buttons.
(but you can skip this option if you are happy with your digital/analog outputs in your arduino). 

(one multiplexer named mux2 it's for 16 digital outputs and the other multiplexer , named mux3, it's for 16 analog outputs).

-I have used 16 analog potentiometers and 23 digital buttons in my pedalboard.

![5device](https://user-images.githubusercontent.com/80991642/187542120-98b99f54-b492-4334-b6bf-820c780a9d51.jpg)

![4device](https://user-images.githubusercontent.com/80991642/187542100-68c962b5-17a8-4d62-9e4d-8299dec1d4be.jpg)

(you can use whatever you want.. but i recommend 15 buttons and 8 potentiometers, minimum).

-Using 8 leds and 8 momentary push button. 

![1device](https://user-images.githubusercontent.com/80991642/187542012-1ccc2f19-bc21-490f-85e6-e05d2184799f.jpg)

The leds are showing the pedal-state, if the pedal it's on or off.
(8 pedals are available for control ON/OFF JUST IN THE MOMENTO!!!)

So you push the micro foot-switch button and the pedal goes to ON and the led turns on the green-light.
And you push it , once more... and the pedal goes to OFF and the led goes to OFF too.
So this 8 buttons and their 8 leds reflects the real pedal-state on/off ALWAYS!! (and just in the momento).



So you open a MIDI track in your DAW or execute standalone plugin and you can (right click) "Midi learn" every potentiometer or parameter on the vst-plugin screen.

Moving potentiometer or pressing the button, the action will be recorded.
You must select "All midi inputs" in the midi track.
And select your vstplugin at midi output , please be sure to enable monitor in this midi track and the midi track it's selected (left click mouse and track it's selected) (see arrow 1 in picture) when you use the midi controller..., in order to get everything working fine, this happens with every midi controller on market...


![Sin nombre](https://user-images.githubusercontent.com/80991642/187542268-78b4f9dd-88c4-4e97-b26e-4ea88f854065.jpg)

-Using the other leds (8 leds more..) for showing the bank position.(four leds for showing the bankamp position and four leds for showing the bankpedal position).

Bank positions 1-4 are green led coloured, and bank positions 5-8 are blue led coloured.

-2 banks (named bankamp and bankpedal).8 different positions on each bank:


** - (Bankpedal= 8 pedals available and 4 potentiometers on each pedal) 
You will use two buttons on BANKPEDAL.. one button it's for increment and the other one it's for decrement the bank position on bankpedal.(see picture, 2 black buttons)
(8 pedals and 4 pots each pedal).(and here you got another one extra button, the red one button,  for turn ON/OFF the pedal effect where you are).


** - (bankamp= 8 different positions for control amps or racks, 4 potentiometers available on each bank).
You will use two buttons on BANKAMP... one button it's for increment and the other one it's one for decrement the bank position on bankamp.
(8 amps or racks and 4 pots each amp or rack).

Please, notice in the pedalboard picture there are more potentiometers than in the code (4 potentiometer works better than 8 ).


*Using i2c lcd screen for showing 8 potentiometers graph-bars , the screen shows the volume bar for 8 potentiometer


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
