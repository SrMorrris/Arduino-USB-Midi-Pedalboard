 # THIS PROJECT WAS MY FIRST DEVICE...AND IT'S OUTDATED...NOW I AM INTERESTED ON ANOTHER MIDI PROJECTS.

I don´t think i will be update this files...anymore..

You can see all my MIDI devices on my principal web-page or my github repositories.

https://srmorrris.github.io/AH-HI-MAHI-WEB-OS-/

But now, i can show you my first device, built with an arduino.

<a href="https://imgbb.com/"><img src="https://i.ibb.co/fNmmLCJ/172305-281f032dea-1.png" alt="172305-281f032dea-1" border="0"></a>


 # Arduino-USB-MIDI-footswitch


Build a Pedal-board for use it in your DAW's (cubase,etc..) or VST plugins (like amplitube,guitar rig,etc..).

You can use whatever Arduino board you want..

If you use a MEGA or UNO, the board needs to be flashed, in the Atmega8u2 or the Atmega16u2 chip in order to get USB-MIDI comunication. 

Be aware that certain boards can't be flashed..like the CH340G boards.., in this cases you will need other pc-programs in order to get the MIDI comunication (this programs are hairless, loopbe1, midiyoke, etc..).

Watch this..


This MEGA board can be flashed into HIDUINO:


<a href="https://imgbb.com/"><img src="https://i.ibb.co/wpT36hC/172224-860a32072d.png" alt="172224-860a32072d" border="0"></a>

Maybe you can't see it in this picture, but there´s a very tiny chip named at16u2 and one ICSP port, attached to this chip.



This MEGA board can't be flashed into HIDUINO (CH340Gchip, there's no atmel16u2 usb-chip):

<a href="https://imgbb.com/"><img src="https://i.ibb.co/RPdg58L/172225-860a32072d.png" alt="172225-860a32072d" border="0"></a>

You can notice, in the last picture, there's a "quartz crystal 12 mhz" nearest the CH340G chip.. maybe the atmel 2560 chip it's a good one.. but this board can't be flashed...you will need pc-programs (like hairless,loopbe1, midi-yoke, etc..) in order to get midi-comunication and everything will works fine in your DAW or plugin.

If you use LEONARDO OR TEENSY, etc.. you will only need to upload one sketch for achieve the MIDI comunication (or adding only one line into your sketch).

You can build your own arduino board , with atmel 328 or 1284 chips, etc..


 # Materials Pedalboard:

 
-*Arduino board. (MEGA,UNO,LEONARDO,ETC,ETC...)
  
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
	
-*16 RGB leds (cathode common) 

 but you can use whatever led-model you want, the better... the cheapest one... but you must think that you will need more than 16 RGB leds.. with single coloured leds you will need 24 leds...

 2 banks with 8 positions each bank, gives 16 leds, and plus... 8 pedal switches, the "just in momento" ones... Total=24 leds , with the rgb leds you will only need 8 leds, but each led its RGB, so each led got 4 pins...8x4=32..

-*1 lcd screen (I2C 20x04). 

 
 # How to.. build your pedalboard...
							  
-Firstly, Install the required libraries for arduino IDE.  (Control.Surface, encoder,etc.. you will see this in include libraries in my sketch).

-Install Hiduino firmware (in order to get usb-midi communication). 

(ARDUINO UNO or MEGA needs to be flashed into USB-MIDI).

Or you can use another way to get usb-MIDI comunication using programs like hairless, or loopbe1, etc... 

    NOTE: Arduino uses usb-serial comunication (CH340G are not the best ones for MIDI..i think..), but you    will need the usb-MIDI comunication.  (you need to comunicate with your DAW or plugin).
    So you can use other pc-programs like hairless,loopbe1,midi-yoke, etc.. for usb-MIDI comunication, but i have prefer the hiduino firmware (pimp my moco lufa, or usb midiklik )
    Hiduino brings the native USB-MIDI comunication (teensy or leonardo only needs to upload an sketch).
    So you connect your usb and the device will be recognized as an USB-Midi device.
    When your arduino it's on usb-Midi comunication will be notice that you can´t upload sketches to your arduino (you will need to come back to serial-usb comunication for being allow to upload sketches).
    People uses "atmel flip" for the flashing-proccess into hiduino and then reflash into arduino for upload sketches.
    But you can implement a switch for change into hiduino or arduino state (midi or serial) (see tutorials about hiduino or pimpmymocolufa, etc..)   

  I have followed this video in order to get the hiduino/arduino switch.(With my Mega2560).

  https://www.youtube.com/watch?v=ITJnWoss8xE&ab_channel=DanielMarcial


-Upload the sketch "Usb_MIDI_Pedal_board Arduino.ino" into your arduino. That´s it.

 # How it works..


-Using multiplexers for more analog and digital outputs in arduino...

Gives more analog potentiometers and more digital buttons.
(but you can skip this option if you are happy with your digital/analog outputs in your arduino). 

(one multiplexer named mux2 it's for 16 digital outputs and the other multiplexer , named mux3, it's for 16 analog outputs).

-I have used 16 analog potentiometers and 23 digital buttons in my pedalboard.

<a href="https://imgbb.com/"><img src="https://i.ibb.co/Xj2LYsz/5device.jpg" alt="5device" border="0"></a>

<a href="https://imgbb.com/"><img src="https://i.ibb.co/vJkgkBW/4device.jpg" alt="4device" border="0"></a>

(you can use whatever you want.. but i recommend 15 buttons and 8 potentiometers, minimum).

-Using 8 leds and 8 momentary push button. 

<a href="https://imgbb.com/"><img src="https://i.ibb.co/7tqxj4G/1device.jpg" alt="1device" border="0"></a>

The leds are showing the pedal-state, if the pedal it's on or off.

(8 pedals are available for control ON/OFF JUST IN THE MOMENTO!!!)

So you push the micro foot-switch button and the pedal goes to ON and the led turns to on the green-light).

And you push it , once more... and the pedal goes to OFF and the led goes to OFF too).

So this 8 buttons and 8 leds reflects the real pedal-state on/off ALWAYS!! (and just in the momento).


So you open a MIDI track in your DAW or execute standalone plugin and you can "Midi learn" every potentiometer or parameter on the plugin screen.

Moving potentiometer or pressing the buttons, the action will be recorded.
You must select "All midi inputs" in the midi track.
And select your plugin at midi output , please be sure to enable monitor in this midi track and the midi track it's selected (left click mouse and track selected) (see arrow 2 in picture) when you use the midi controller..., in order to get everything working fine, this happens with every midi controller on market...

<a href="https://ibb.co/18g0pJV"><img src="https://i.ibb.co/72fSTNc/Sin-nombre.jpg" alt="Sin-nombre" border="0"></a>

-Using the other leds (8 leds more..) for showing the bank position.(four leds for show the bankamp position and four leds for show the  bankpedal position).

Bank positions 1-4 are green led coloured and 5-8 are blue led coloured.

2 banks (named bankamp and bankpedal).8 different position each bank:



**-(Bankpedal=8 pedals available and 4 potentiometer on each pedal) 
You will use two buttons on BANKPEDAL.. one button it's for increment and the other one it's for decrement the bank position on bankpedal.
(8 pedals and 4 pots each pedal).(and here you got another one extra button for turn ON/OFF the pedal effect).



**-(bankamp=8 different positions for control amps or racks, 4 potentiometer available on each bank).
You will use two buttons on BANKAMP... one button it's for increment and the other it's one for decrement the bank position on bankamp.
(8 amps or racks and 4 pots each amp or rack).




*Using i2c lcd screen for showing 8 potentiometers graph-bars , the screen shows the volume bar for 8 potentiometer


<a href="https://imgbb.com/"><img src="https://i.ibb.co/0J6XHsh/3device.jpg" alt="3device" border="0"></a>

<a href="https://imgbb.com/"><img src="https://i.ibb.co/WpF8JWQ/2device.jpg" alt="2device" border="0"></a>


I have quit of this project, i have been updated every day during one month and i have achieved 16 volume bars for each potentiometer (16 graph-bars on screen )..one volume/wah pedal.. one encoder... but i have quited because i have found some other MIDI projects so much better than this one...


  THIS PROJECT WAS MY FIRST DEVICE...HAS BEEN OUTDATED BY ANOTHER USB-MIDI PROJECTS. But you can ask me about it..
