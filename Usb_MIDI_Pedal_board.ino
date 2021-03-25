/***********************************************************************************
 ********************     USB MIDI FOOTSWITCH     **********************************
 *********************       ARDUINOMEGA2560     ***********************************
 **********************      CONTROL.SURFACE    ************************************
 ****  Install libraries... Control.Surface library.  *********************** 
 ************   NewLiquidCrystal .LcdBarGraphx . Encoder..     ********************* 
 ***********************************************************************************
 ****In order o declare arduino as usbMIDI interface, first you will need  to flash 
 * your arduino and convert into hiduino or you can use other programs  
 * like "loopbe1" or "hairless"..in order to use usbmidi comunication 
 * on arduino and not the serial comunication. See control.surface for 
 * other interfaces. 
 ***********************************************************************************
 ***********************************************************************************
 ***********************************************************************************
 ******** For "La pedalera del tio Elias" Arduino.Usb-Midi.MultiBank Footswitch.****
 ********************             You will need:               *********************
 *********************************************************************************** 
 **      -   An arduino board (Mega2560 it's the perfect model for me).
 ***********************************************************************************  
 *****   -   2 CD74HC4067 multiplexers (perfect for bring more inputs..)
 *           i don´t recommend using outputs on multiplexer...but it´s perfect for 
 *           INPUTS. You can declare the multiplexer as digital or analog multiplexer).
 *           For output use shift registers,
 ***********************************************************************************      
 *****   -   16 Lineal Potentiometers 10k.
 ***********************************************************************************
 ****    -   21 Buttons (momentar,microswitch, normally closed,pushbutton.etc..)
 *********************************************************************************** 
 *****   -   Encoder.        
 * *********************************************************************************.
 *****   -   Lcd 20x04 I2C screen (i recommend oled 1306 or another SPI screen).
 ***********************************************************************************  
 *****   -   16 RGB cathode leds (cathode means all leds connected to ground). 
 ***********************************************************************************   
 *****   -   You can use switches for turning back arduinointo serial comunication 
 *              and you will be able to upload sketches...turning off the switch 
 *              you will come back to hiduino and the arduino´s usb-midi comunication.
 *****   -   You will need wire and other electronic build materials(i use the thinnest 
 *              wire i have found on aliexpress but ensure you connect everything 
 *              fine and  correct (not excesive voltage loose on circuit) because bad  
 *              connections will  cause interferences.
 ***********************************************************************************         
 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       
 -----------------------------------------------------------------------------------
 */
#include <AnalogMultiButton.h>
#include <LcdBarGraphX.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Encoder.h>
#include <Control_Surface.h>  
#include <Arduino_Helpers.h> // Include the Arduino Helpers library.
#include <AH/Containers/ArrayHelpers.hpp>
#include <AH/Hardware/Button.hpp>
#include <AH/Hardware/ExtendedInputOutput/AnalogMultiplex.hpp>
#include <AH/Hardware/ExtendedInputOutput/SPIShiftRegisterOut.hpp>
#include <LiquidMenu.h>
#include <hd44780.h>
#include <LCD.h>

USBMIDI_Interface usbmidi;   
 
/**Declare ENCODER.connect pins 18, 19 on arduino as outputs named 
 * outputA and outputB and connect pin 4 on arduino(button encoder)                */
#define outputA 18
#define outputB 19
#define sw 4

int aState;
int aLastState;  

const int speedMultiplier = 1;  // Variable for the Encoder

/*Declare number of columns on lcd screen (20)..change this number to 16 for 
 * 16x02 screens                                                                  */
byte lcdNumCols = 20;
 
/**Declare a LCD screen, I2C comunication, 0x27 address device                    */ 
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#define LCD_COLS 20
#define LCD_ROWS 4
 
/**Next lines prints four graphbars in LCD using two part of the lines on the screen,
  *Graphbars shows four potentiometers analogRead value for four
    Amps and racks banked potentiometers.                                         */
LcdBarGraphX lbg0(&lcd, 4, 1, 0); // -- First Bar-graph at column 1, line 1, 4barsgraph.
LcdBarGraphX lbg1(&lcd, 4, 6, 0); // -- Second Bar-graph at column 6, line 1, 4barsgraph.
LcdBarGraphX lbg2(&lcd, 4, 1, 1); // -- Third Bar-graph at column 1, line 2, 4barsgraph.
LcdBarGraphX lbg3(&lcd, 4, 6, 1); // -- Fourth Bar-graph at column 6, line 2, 4barsgraph.

/**Next lines prints four graphbars in LCD using two part of the lines on the screen,
  *Graphbars shows four potentiometers analogRead value for four       
    Pedal banked potentiometers.                                                  */
LcdBarGraphX lbg4(&lcd, 4, 11, 0); // -- First Bar-graph at column 11, line 1, 4barsgraph.
LcdBarGraphX lbg5(&lcd, 4, 16, 0); // -- Second Bar-graph at column 16, line 1, 4barsgraph.
LcdBarGraphX lbg6(&lcd, 4, 11, 1); // -- Third Bar-graph at column 11, line 2, 4barsgraph.
LcdBarGraphX lbg7(&lcd, 4, 16, 1); // -- Fourth Bar-graph at column 16, line 2, 4barsgraph.

/*Next lines are under construction..will be used for show which pedal its activated
 * and print this INFO on the screen                                              */
                                                                    
LcdBarGraphX lbg8(&lcd, 2, 3, 3); // -- First line at column 0
LcdBarGraphX lbg9(&lcd, 2, 4, 2); // -- First line at column 5


Bank<8> bankpedal(4); //Declare a bank named bankpedal.<8>bank positions.and(4)incrementDecrement value
Bank<8> bankamp(4);   //Declare a bank named bankpedal.<8>bank positions.and(4)IncrementDecrement value

/**Declare a CD74HC4067 multiplexer "mux2".*/
CD74HC4067 mux2 = { 
  8,                //Pin SIG on multiplexer, connected to pin(8) on arduino.
  {9, 10, 11, 12},  //Pins S0, S1, S2, S3 on multiplexer, connected to pins( 9, 10, 11 and 12 )on arduino.
 };

/**Declare 8 mux2 pins as digital output CCButtonLatched named pedalswitches     */
CCButtonLatched pedalswitches [] = {          
  { mux2.pin(0), { 77, CHANNEL_1 } },   //connected to C0 multiplexer(mux2).CC77 output MIDI signal on channel 1.   
  { mux2.pin(1), { 81, CHANNEL_1 } },   //connected to C1 multiplexer(mux2).CC81 output MIDI signal on channel 1.  
  { mux2.pin(2), { 85, CHANNEL_1 } },   //connected to C2 multiplexer(mux2).CC85 output MIDI signal on channel 1.                                                 
  { mux2.pin(3), { 89, CHANNEL_1 } },
  { mux2.pin(4), { 93, CHANNEL_1 } },
  { mux2.pin(5), { 97, CHANNEL_1 } },
  { mux2.pin(6), { 101, CHANNEL_1 } },
  { mux2.pin(7), { 105, CHANNEL_1 } },
 }; 
/**Next const int variables will be used on lcd                                  */
const int i8 = mux2.pin(0);
const int i9 = mux2.pin(1);
const int i10 = mux2.pin(2);
const int i11 = mux2.pin(3);
const int i12 = mux2.pin(4);
const int i13 = mux2.pin(5);
const int i14 = mux2.pin(6);
const int i15 = mux2.pin(7);


CCButtonLatched futton2 [] = {  
  { mux2.pin(8), { 84, CHANNEL_1 } },    
  { mux2.pin(9), { 86, CHANNEL_2 } }, 
  { mux2.pin(10), { 87, CHANNEL_3 } },                                                   
  { mux2.pin(11), { 88, CHANNEL_4 } },
  { mux2.pin(12), { 90, CHANNEL_5 } },
  { mux2.pin(13), { 91, CHANNEL_6 } },
  { mux2.pin(14), { 92, CHANNEL_7 } },
  { mux2.pin(15), { 94, CHANNEL_8 } },
};

CD74HC4067 mux3 = {
  A15,            
  {A14, A13, A12, A11}, 
  };

const int i0 = mux3.pin(8);
const int i1 = mux3.pin(9);
const int i2 = mux3.pin(10);
const int i3 = mux3.pin(11);
const int i4 = mux3.pin(0);
const int i5 = mux3.pin(1);
const int i6 = mux3.pin(2);
const int i7 = mux3.pin(3);

CCPotentiometer pots3 [] = {

  {mux3.pin(4), 74},
  {mux3.pin(5), 75},
  {mux3.pin(6), 76},
  {mux3.pin(7), 78},
  {mux3.pin(12), 79},
  {mux3.pin(13), 80},
  {mux3.pin(14), 82},
  {mux3.pin(15), 83},
  };

Bankable::CCButtonLatched<8>  bankbuttons [] = {  
  { bankpedal, 6, 77, },  
  //{ bankpedal, 6, 91, },
  };

Bankable::CCPotentiometer pots[] = {   
  
  {bankamp, mux3.pin(8), 1},
  {bankamp, mux3.pin(9), 3},
  {bankamp, mux3.pin(10), 4},
  {bankamp, mux3.pin(11), 6},
};
 
Bankable::CCPotentiometer pots2[] = {    
  
  {bankpedal, mux3.pin(0), 37},
  {bankpedal, mux3.pin(1), 38},
  {bankpedal, mux3.pin(2), 39},
  {bankpedal, mux3.pin(3), 40},
};

IncrementDecrementSelectorLEDs<8> bankSelector = {   
  bankpedal,
  {5, 7},         // button pins
  {30, 31, 32, 33, 34, 35, 36, 37}, // LED pins
  }; 

IncrementDecrementSelectorLEDs<8> bankSelector2 = {   
  bankamp,
  {14, 15},         // button pins
  {38, 43, 44, 41, 42, 39, 40, 45}, // LED pins
  };

CCRotaryEncoder enc = {
  
  {18, 19},                                // pins
  76,                                     // address
  speedMultiplier,                       // multiplier
  4,                                     // pulses per click
};


const pin_t ledPins[] = { 22, 23, 24, 25, 26, 27, 28, 29 };

template <class T, size_t N> constexpr size_t length(T (&)[N]) { return N; }

static_assert(length(pedalswitches) == length(ledPins),
              "Error: requires same number of buttons as LEDs");



void setup() {

    Control_Surface.begin();
    
 for (auto pin : ledPins)       //Set the pinMode to output for all LEDs
      pinMode(pin, OUTPUT);
      pinMode(sw,INPUT_PULLUP); //encoder pin(4) will be connected to +5volts with pull-up resistor

  // -- initializing the LCD
  lcd.begin(4, lcdNumCols);
  lcd.clear();
  lcd.begin(4, lcdNumCols);
  lcd.clear();
  lcd.begin(4, lcdNumCols);
  delay(150);
  lcd.clear();
  lcd.begin(4, lcdNumCols);
  delay(100);
  lcd.clear();
  lcd.begin(4, lcdNumCols);
  delay(150);
  lcd.clear();
  lcd.begin(4, lcdNumCols);
  lcd.setCursor(0,2);
  lcd.print ("Al loro.......");
  delay(1000);
  lcd.setCursor (5,3);
  lcd.print ("NENES...NENAS..");
  delay(800);
  lcd.clear();
  lcd.setCursor(1,2);
  lcd.print ("ELSEREBROLABESTIA");
  delay(800);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print ("LA PEDALERA USB MIDI");
  delay(500);
  lcd.setCursor(1,3);
  lcd.print ("Del Tio Elias");
  delay(1000);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print ("YA ESTA AQUI!");
  delay(800);
  lcd.clear();
   lcd.setCursor(12,0);
  lcd.print ("jar");
  delay(500);
  lcd.clear();
 



 }

void loop() {
  Control_Surface.loop();
  
 for (size_t i = 0; i < length(pedalswitches); ++i)
      // Update the LED states to reflect the toggled switch states
      digitalWrite(ledPins[i], pedalswitches[i].getState() ? LOW : HIGH);

  lbg0.drawValue( analogRead(i0), 1023);
  lbg1.drawValue( analogRead(i1), 1023);
  lbg2.drawValue( analogRead(i2), 1023);
  lbg3.drawValue( analogRead(i3), 1023);
  lbg4.drawValue( analogRead(i4), 1023);
  lbg5.drawValue( analogRead(i5), 1023);
  lbg6.drawValue( analogRead(i6), 1023);
  lbg7.drawValue( analogRead(i7), 1023);

  
  lcd.setCursor(0,2);
  lcd.print("Amp-Rack<POTS>");
  lcd.setCursor(14,2);
  lcd.print("Pedal");
  lcd.setCursor(0,3);
  lcd.print("SWI");
  lcd.setCursor(0,0);
  lcd.print("1");
  lcd.setCursor(0,1);
  lcd.print("3");
  lcd.setCursor(5,0);
  lcd.print("2");
  lcd.setCursor(5,1);
  lcd.print("4");
   lcd.setCursor(10,0);
  lcd.print("1");
  lcd.setCursor(10,1);
  lcd.print("3");
  lcd.setCursor(15,0);
  lcd.print("2");
  lcd.setCursor(15,1);
  lcd.print("4");

lbg8.drawValue( analogRead(i8), 1023);
 //lbg9.drawValue( digitalRead(i9), 1023);
  }
 




 

 
