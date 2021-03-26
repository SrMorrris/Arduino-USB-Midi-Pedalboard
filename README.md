 # ArduinoMIDIfootswitch

Build a Pedal board to use on your DAW´s (cubase,ableton,etc) or plugins (amplitube,guitar rig,etc..).

Materials:
 
  -*Arduino.
  
  -*One switch :used to change between arduino usb serial comunication or									 									
	the hiduino usb midi comunication on your arduino. The switch ON/OFF it´s connected 
    to 2 pins arduino (atmel16u2 ICSP) (see hiduino tutorials how to achieve it). 

   -*23 Buttons :(11 buttons will be used for foot-switching)
	
   -*2 multiplexers cd74hc4067.  : (more digital or analog inputs for arduino)
	
   -*16 potentiometers 10k.

   -*24 220 ohms resistors for leds.
	
   -*16 RGB leds (cathode common)(but you can use whatever led-model you want,
    better the cheapest one...but think you will need more than 16 RGB leds..
    with single coloured leds you will need 24 leds).
	two banks with eight positions each bank and 8 pedal switches ON/OFF. Total=24 leds)

   OPTIONAL(under construction)

   *lcd screen (I2C 20x04). (but much better if you got an oled SPI screen). 

   *Encoder

   *JACK female 6,5 mm (for connecting expression/volume pedals to analog 
	inputs in arduino or multiplexer) 

   *more,more,more updates (soon)...
   
	
   HOW TO build your pedalboard

-Build your pedalboard.(i give you one example)									  

-Install libraries for arduino IDE.  (Control.Surface, encoder,etc.. you will see include libraries on the sketch)

-Install Hiduino firmware (for usb-midi communication).
Or you can use another way to get usbMIDI comunication using programs like hairless, or loopbe1, etc..). 

   NOTE:Arduino uses usb serial comunication, but you will need usb MIDI comunication 
 (in order to get recognised device for daws). 
  So you can use other programs like hairless,loopbe1,etc.. for usb MIDI comunication,but i have prefer hiduino firmware.
  When your arduino it´s on usb Midi comunication notice that you can´t upload sketches to your arduino 
  (you need to come back to serial usb comunication).
  People uses "atmel flip" for the flash proccess into hiduino and then reflash to arduino for upload sketches.
  You can implement one switch for change into hiduino or arduino state (see tutorials about hiduino or pimpmymocolufa).


-Upload the sketch "Usb_MIDI_Pedal_board Arduino.ino" to your arduino.




Using multiplexers for more analog and digital inputs on arduino. Connecting analog potentiometers and digital buttons 
(but you can skip this option if you are happy with digital/analog inputs amount on your arduino)). 
(one multiplexer named mux2 it´s for 16 digital inputs and the other multiplexer , named mux3, it´s for 16 analog inputs).

I have used 16 analog potentiometerss and 23 digital buttons.
(you can use whatever you want but i recommend 15 buttons and 8 potentiometers at least).

Using 8 leds and 8 momentary push button The leds are showing the pedal state if it´s on or off .
(8 pedals available for control with your pedalboard).
(so you push the button and the pedal goes to ON and the led turns on the green light)
(you push once more and the pedal goes to OFF and the led goes to OFF too).
So this 8 buttons and 8 leds reflects the real pedal state on/off. you can turn on/off quickly each pedal and see the state.

Using other leds (8 leds more) for show the bank position.(four leds for show bankamp position and four leds for show bankpedal position).
Bank positions 1-4 are green led coloured and 5-8 are blue led coloured.

2 banks (named bankamp and bankpedal).8 different position each bank.
-(bankpedal=8 pedals available and 4 potentiometer on each pedal) 
-(bankamp=8 different positions for control amps or racks, 4 potentiometer available on each bank).

You will use two buttons one button for increment and the other one for decrement the bank position on bankpedal.
 (8 pedals and 4 pots each pedal).(you got one extra button for turn ON/OFF the pedal effect).
You will use two buttons one button for increment and the other one for decrement the bank position  on bankamp.
 (8 amps or racks and 4 pots each amp or rack).

*Using i2c lcd screen for showing 8 potentiometers graphbars (early stages right now).

*dreaming about more updates (control.surface it's my god)
