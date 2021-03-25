# ArduinoMIDIfootswitch
Build a Pedal board to use on your DAW´s (cubase,ableton,etc) or plugins (amplitube,guitar rig,etc..)

*Arduino.
-One switch to change arduino usb serial comunication or hiduino usb midi comunication (switch ON/OFF connected to two pins arduino on atmel16u2 ICSP) (see tutorials hiduino for this) 
*23 Buttons (11 buttons must be for foot-switching)
*2 multiplexers cd74hc4067. (
*16 potentiometers 10k.
*24 220 ohms resistors for leds.
*16 RGB leds (cathode common)(but you can use whatever led-model you want, better the cheapest one...but you will need more than 16 RGB leds..you will need 24 leds).
OPTIONAL(under construction)
*lcd screen (I2C 20x04). (but much better if you got an oled SPI screen).
*Encoder
*JACK female 6,5 mm (for connecting expression/volume pedals to analog inputs in arduino or multiplexer) 
*


-Install libraries for arduino IDE like Control.Surface library. (or encoder,etc..)
-Install Hiduino firmware (for usb-midi communication).(or use programs like hairless,etc)
-Upload code.



Arduino use usb serial comunication,but you will need usb MIDI comunication. You can use programs like hairless,loopbe,etc..
When your arduino it´s on usb Midi comunication you can´t upload sketches to your arduino (you need to come back to serial usb comunication)

 
Using multiplexers for analog potentiometers and digital buttons (you can skip this option) (one multiplexer digital inputs and the other multiplexer analog inputs)
I have used 16 analog pots and 23 digital buttons.
Using 8 leds with 8 momentary push button indicates the pedal state on or off (8 pedal available for control).
Using other leds (8 leds more) for show bank position.(four leds for show bankamp position and four leds for show bankpedal position).
Bank positions 1-4 are green  and 5-8 are blue .

2 banks (bankamp and bankpedal).8 different position for each bank 
-(bankpedal=8 pedals available 4 potentiometer on each pedal) 
-(bankamp=8 different positions for control amps or racks, 4 potentiometer available on each bank).

*Using i2c lcd screen for showing 16 potentiometers graphbars (early stages right now).

*dreaming about more updates (control.surface it's god)
