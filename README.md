# ArduinoMIDIfootswitch
Build a Footswitch to use on your DAW´s.
*Arduino
*23 Buttons
*2 multiplexers cd74hc4067
*16 analog potentiometer
*16 leds
*lcd screen (i2c but better SPI) (this part its on construction)

Arduino and Control.Surface library.
Hiduino firmware (for usb-midi communication).
Bring a usb-midi device for pedals ,racks, amps, etc.. on DAW´s (like amplitube,guitar rig,etc..). 
Using multiplexers for analog potentiometers and digital buttons (you can skip this option).(
I have used 16 analog pots and 23 digital buttons.
Using 8 leds with 8 momentary push button indicates the pedal state on or off (8 pedals available).
Using other leds (8 leds more) for show bank position.(four leds for show bankamp position and four leds for show bankpedal position).

2 banks (bankamp and bankpedal).8 different position for each bank 
-(bankpedal=8 pedals available 4 potentiometer on each pedal..so you are changing CC on the pot each bankpedal position) 
-(bankamp=8 different positions and 4 potentiometer change CC each bankamp position).

*Using i2c lcd screen for showing 4 pedalbank potentiometer graphbars (early stages right now).
* Would be possible using two different screens on lcd???one for each bank (bank pedal screen showing pedal potentiometers and bankamp shows another (second)screen for amp potentiometers.
* *Would be possible (get state = active) potentiometers and print.lcd when potentiometers are active??
* so many questions..
*dreaming about more updates (control.surface it's god)
