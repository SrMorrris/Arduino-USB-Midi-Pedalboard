/**************************************************************************************************************
 ********************     USB MIDI FOOTSWITCH     *********************************************************
 *********************       ARDUINOMEGA2560     ***********************************************************
 **********************      CONTROL.SURFACE    **************************************************************
 *********************************************************************************************************   
 ******************************************************************************************************     
 *****************************************************************************************************************
                Install libraries... Control.Surface library.  
                NewLiquidCrystal .LcdBarGraphx . Encoder..etc.etc.etc...    
 ***************************************************************************************************************
 * In order to declare arduino as usbMIDI interface, first you will need  to flash 
 * your arduino and convert it into hiduino , or you can use other programs  
 * like "loopbe1" or "hairless"....in order to use usbmidi comunication 
 * and not the serial comunication on your arduino. See control.surface docu for declare 
 * other interfaces. 
 *****************************************************************************************************************
 **************************************************************************************************************
 ******************************************************************************************************************
 ******** For "La pedalera del tio Elias" Arduino Usb-Midi MultiBank Pedal-Board Super-footswith.*********************************
 ********************             You will need:               ************************************************
 ****************************************************************************************************************** 
 **      -   An arduino board (Mega2560 it's the perfect model for me).
 ******************************************************************************************************************  
 *****   -   2 CD74HC4067 multiplexers (perfect for bring more inputs..)
 *           i don´t recommend using outputs on multiplexer...but it´s perfect for 
 *           INPUTS. You can declare the multiplexer as digital or analog multiplexer).
 *           For output you can use shift registers,
 ************************************************************************************************************************      
 *****   -   16 Lineal Potentiometers 10k.
 ********************************************************************************************************************
 ****    -   21 Buttons (momentar,microswitch, normally closed,pushbutton.etc..)
 ******************************************************************************************************************* 
 *****   -   Encoder.        
 * *******************************************************************************************************************
 *****   -   Lcd 20x04 I2C screen (i recommend oled 1306 or another SPI screen).
 ****************************************************************************************************************** **************** 
 *****   -   16 RGB cathode leds (cathode means all leds connected to ground). 
 ****************************************************************************************************************************   
 *****   -   You can use switches for turning back arduino into serial comunication 
 *              and you will be able to upload sketches...turning off the switch 
 *              you will come back to hiduino and the arduino´s usb-midi comunication.
 *****   -   You will need wire and other electronic build materials(i use the thinnest 
 *              and cheapest wire i have found on aliexpress but ensure you connect everything 
 *              fine and  correct (not excesive voltage loose on circuit) because bad  
 *              connections will  cause interferences.
 *              
 *              
 *Open your Daw. Select your hiduino usb midi device and then press "midi learn" in the plugin or DAW 
 *to configure your pedalboard. 
 *
 *First you can configure the first pedal (select midi learn) with the four bankable potentiometers.
 *And then configure the pedal effect ON/OFF button.or another button in this first pedal,

 *
 *Second:press increment or decrement bank button and then configure the next pedal with the same 
 *4 potentiometers. And don´t forget to configure the pedal effect ON/OFF button.
 *
 * And...so on..until the eight bank position. until the eight pedal or the eight amp/rack 
 * NOTICE:You can turn ON/OFF each pedal effect with two different buttons. 
 * So two different buttons for turn on/off effect on each 8 pedal.
 *
 * * EXAMPLE CONFIG: click mouse right button on your first pedal in amplitube and select "midi learn" 
 * for the gain potentiometer,for example,..then move one bankable potentiometer of your pedalboard..
 * or click mouse right button upon pedal effect ON/OFF and select "midi learn"
 * and press one of the led buttons("pedalswitches") in the pedalboard and then the  button 
 *("pedal-effect.principal-button")of the pedalboard .
 * 
 ******************************************************************************************************************************         
 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX       
 ----------------------------------------------------------------------------------------------------------------------------*/
 
#include <AnalogMultiButton.h>                                         //Will be used for connect two or more buttons,using resistors, to one analog input on arduino.
#include <LcdBarGraphX.h>                                             //Used for display Bar graphs on Lcd screen
#include <LiquidCrystal.h>                                           //Used for LCD I2C screen
#include <LiquidCrystal_I2C.h>                                      //Used for LCD I2C screen
#include <Encoder.h>                                               //Used for encoder
#include <Control_Surface.h>                                      //Include Control Surface library (
#include <Arduino_Helpers.h>                                     //Include the Arduino Helpers library.
#include <AH/Containers/ArrayHelpers.hpp>                       //Include the ArrayHelpers library.
#include <AH/Hardware/Button.hpp>                              //Include the Button library.
#include <AH/Hardware/ExtendedInputOutput/AnalogMultiplex.hpp>//Include the AnalogMultiplex library.
#include <LiquidMenu.h>                                  //Will be used for build a menu and various screens on the lcd
#include <hd44780.h>                                    //Used for LCD I2C screen
#include <LCD.h>                                       //Used for LCD I2C screen

USBMIDI_Interface usbmidi;   
 
/**Declare ENCODER.connect pins 18, 19 and named outputA 
 * and outputB and connect pin 4 on arduino(encoder sw button) */               
#define outputA 18 //  CLK. Clock signal.
#define outputB 19 //  DA. Data signal. (detects move change)
#define sw 4       //  SW. Presure signal (button).

int aState;
int aLastState;  

const int speedMultiplier = 1;  // Variable for the Encoder

/*Declare number of columns on lcd screen (20)..change this number to 16 for 
 * 16x02 screens  */                                                                
byte lcdNumCols = 20;
 
/**Declare a LCD screen, I2C comunication, 0x27 address device */                    
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#define LCD_COLS 20
#define LCD_ROWS 4
 
/**Next lines prints four graphbars in LCD using two part of the lines on the screen,
  *Graphbars shows four potentiometers analogRead value for four
    Amps and racks banked potentiometers. */                                        
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

/**Declare a CD74HC4067 multiplexer named "mux2".*/
CD74HC4067 mux2 = { 
  8,                //Pin SIG on multiplexer, connected to pin(8) on arduino.
  {9, 10, 11, 12},  //Pins S0, S1, S2, S3 on multiplexer, connected to pins( 9, 10, 11 and 12 )on arduino.
 };

/**Declare 8 buttons as ccbuttonlatched and 
*connected to pins 0-7 in multiplexer 2 (mux2) 99, 
*declared as digital inputs and named "pedalswitches" .
*Will be the 8 on/off buttons for 8 different pedals
*/
CCButtonLatched pedalswitches[] = {          
  { mux2.pin(0), { 77, CHANNEL_1 } },   //Button connected to C0 in multiplexer(mux2)and Ground. CC 77 MIDI signal on channel 1. First pedal effect on/off button (with led state)  
  { mux2.pin(1), { 81, CHANNEL_1 } },   //Button connected to C1 in multiplexer(mux2)and Ground. CC 81 MIDI signal on channel 1. Second pedal effect on/off button (with led state)
  { mux2.pin(2), { 85, CHANNEL_1 } },   //Button connected to C2 in multiplexer(mux2)and Ground. CC 85 MIDI signal on channel 1. Third pedal effect on/off button (with led state)                                               
  { mux2.pin(3), { 89, CHANNEL_1 } },   //Button connected to C3 in multiplexer(mux2)and Ground. CC 89 MIDI signal on channel 1.  Fourth pedal effect on/off button (with led state)
  { mux2.pin(4), { 93, CHANNEL_1 } },   //Button connected to C4 in multiplexer(mux2)and Ground. CC 93 MIDI signal on channel 1. Fifth pedal effect on/off button (with led state)
  { mux2.pin(5), { 97, CHANNEL_1 } },   //Button connected to C5 in multiplexer(mux2)and Ground. CC 97 MIDI signal on channel 1. Sixth pedal effect on/off button (with led state)
  { mux2.pin(6), { 101, CHANNEL_1 } },  //Button connected to C6 in multiplexer(mux2)and Ground. CC 101 MIDI signal on channel 1. Seventh pedal effect on/off button (with led state)
  { mux2.pin(7), { 105, CHANNEL_1 } },  //Button connected to C7 in multiplexer(mux2)and Ground. CC 105 MIDI signal on channel 1. eighth pedal effect on/off button (with led state)
 }; 
/**Next const int variables will be used on lcd */                                 
const int i8 = mux2.pin(0);
const int i9 = mux2.pin(1);
const int i10 = mux2.pin(2);
const int i11 = mux2.pin(3);
const int i12 = mux2.pin(4);
const int i13 = mux2.pin(5);
const int i14 = mux2.pin(6);
const int i15 = mux2.pin(7);

/**Declare 8 buttons as ccbuttonlatched type and 
 * connected to pins 8-15 in multiplexer 2 (mux2),  
 * as digital inputs, "named single8buttons"   */
 
CCButtonLatched single8buttons[] = {  
  { mux2.pin(8), { 84, CHANNEL_1 } },    //Button connected to C8 in multiplexer(mux2)and Ground. CC 84 MIDI signal on channel 1.
  { mux2.pin(9), { 86, CHANNEL_2 } },    //Button connected to C9 in multiplexer(mux2)and Ground. CC 86 MIDI signal on channel 2.
  { mux2.pin(10), { 87, CHANNEL_3 } },   //Button connected to C10 in multiplexer(mux2)and Ground. CC 87 MIDI signal on channel 3.                                               
  { mux2.pin(11), { 88, CHANNEL_4 } },   //Button connected to C11 in multiplexer(mux2)and Ground. CC 88 MIDI signal on channel 4.
  { mux2.pin(12), { 90, CHANNEL_5 } },   //Button connected to C12 in multiplexer(mux2)and Ground. CC 90 MIDI signal on channel 5.
  { mux2.pin(13), { 91, CHANNEL_6 } },   //Button connected to C13 in multiplexer(mux2)and Ground. CC 91 MIDI signal on channel 6.
  { mux2.pin(14), { 92, CHANNEL_7 } },   //Button connected to C14 in multiplexer(mux2)and Ground. CC 92 MIDI signal on channel 7.
  { mux2.pin(15), { 94, CHANNEL_8 } },   //Button connected to C15 in multiplexer(mux2)and Ground. CC 77 MIDI signal on channel 1.
};

/**Declare a CD74HC4067 multiplexer named "mux3".*/
CD74HC4067 mux3 = {
  A15,                     //Pin SIG on multiplexer, connected to pin(A15) on arduino.
  {A14, A13, A12, A11},    //Pins S0, S1, S2, S3 on multiplexer, connected to pins( A14, A13, A12 and A11 )in arduino.
  };

/**Next const int variables will be used on lcd */  
const int i0 = mux3.pin(8);
const int i1 = mux3.pin(9);
const int i2 = mux3.pin(10);
const int i3 = mux3.pin(11);
const int i4 = mux3.pin(0);
const int i5 = mux3.pin(1);
const int i6 = mux3.pin(2);
const int i7 = mux3.pin(3);

/**Declare 8 potentiometers as ccpotentiometer type and 
 * connected to pins 4-7 (POTSpedal) and 12-15 (POTSamps).  
 * Declared as analog inputs in multiplexer 3 (mux3), ,and named "POTSpedalPOTSamp"   */
 
CCPotentiometer POTSpedalPOTSamp[] = {

  {mux3.pin(4), 74},     //Potentiometer connected to C4 in multiplexer(mux3)and Ground. CC 74 MIDI signal on channel 1. Pots pedal (not bankable)
  {mux3.pin(5), 75},     //Potentiometer connected to C5 in multiplexer(mux3)and Ground. CC 75 MIDI signal on channel 1. Pots pedal (not bankable)
  {mux3.pin(6), 76},     //Potentiometer connected to C6 in multiplexer(mux3)and Ground. CC 76 MIDI signal on channel 1. Pots pedal (not bankable)
  {mux3.pin(7), 78},     //Potentiometer connected to C7 in multiplexer(mux3)and Ground. CC 78 MIDI signal on channel 1. Pots pedal (not bankable)
  {mux3.pin(12), 79},    //Potentiometer connected to C12 in multiplexer(mux3)and Ground. CC 79 MIDI signal on channel 1.Pots amp (not bankable)
  {mux3.pin(13), 80},    //Potentiometer connected to C13 in multiplexer(mux3)and Ground. CC 80 MIDI signal on channel 1.Pots amp (not bankable)
  {mux3.pin(14), 82},    //Potentiometer connected to C14 in multiplexer(mux3)and Ground. CC 82 MIDI signal on channel 1.Pots amp (not bankable)
  {mux3.pin(15), 83},    //Potentiometer connected to C15 in multiplexer(mux3)and Ground. CC 83 MIDI signal on channel 1.Pots amp (not bankable)
  };


/** Declare a button as bankable::ccbuttonlatched type 
 * (this button will increment or decrement (4) values (CC)
 *  in <8> each bank position (bankpedal).(Starts on position one
 *  77 CC and finish position eight 105 CC).
 *  it´s connected to pin 6 in arduino,  
 * declared as digital input,and named "pedaleffectprincipalbutton" 
 * This button will turn ON/OFF the pedal effect.
 * pressing increment/decrement button will turn on/off the next pedal effect.
 */
Bankable::CCButtonLatched<8>  pedaleffectprincipalbutton[] = {  
  { bankpedal, 6, 77, },    
  };


/**Declare 4 potentiometers as bankable::ccpotentiometer type and 
 * connected to pins 8-11  in multiplexer 3 (mux3),  
 * declared as analog inputs,and named POTSbankamp. 
 * (this potentiometers will increment or decrement (4) values (CC)
 *  in <8> each bank position (bankamp).(First potentiometer starts on position one
 *  1 CC and finish position eight 29 CC).
 */
Bankable::CCPotentiometer POTSbankamp[] = {   
  
  {bankamp, mux3.pin(8), 1},
  {bankamp, mux3.pin(9), 3},
  {bankamp, mux3.pin(10), 4},
  {bankamp, mux3.pin(11), 6},
};


 /**Declare 4 potentiometers as bankable::ccpotentiometer type and 
 * connected to pins 0-3  in multiplexer 3 (mux3),  
 * declared as analog inputs,and named POTSbankpedal. 
 * (this potentiometers will increment or decrement (4) values (CC)
 *  in <8> each bank position (bankamp).(First potentiometer starts on position one
 *  37 CC and finish position eight 65 CC).
 */
Bankable::CCPotentiometer POTSbankpedal[] = {    
  
  {bankpedal, mux3.pin(0), 37},
  {bankpedal, mux3.pin(1), 38},
  {bankpedal, mux3.pin(2), 39},
  {bankpedal, mux3.pin(3), 40},
};


/** Declare two buttons as Incrementdecrementselectorleds type 
 * (this buttons will increment or decrement bank position
 *  in bankpedal.(Starts on position one and finish in position eight)
 *  declared as digital inputs,and named "bankSelectorbankpedal" 
 * This buttons will show bank position from one to eight with eight 
 * different leds
 */
IncrementDecrementSelectorLEDs<8> bankSelectorbankpedal = {   
  bankpedal,
  {5, 7},                           // button pins connected to digital inputs 5 and 7 in arduino and ground
  {30, 31, 32, 33, 34, 35, 36, 37}, // LED pins connected to digital inputs 30-37 in arduino and ground
  }; 


/** Declare two buttons as Incrementdecrementselectorleds type 
 * (this buttons will increment or decrement bank position
 *  in bankamp.(Starts on position one and finish in position eight)
 *  declared as digital inputs,and named "bankSelectorbankamp" 
 * This buttons will show bank position 1-8 with eight 
 * different leds
 */
IncrementDecrementSelectorLEDs<8> bankSelectorbankamp = {   
  bankamp,
  {14, 15},                         // buttons connected to digital inputs 14 and 15 in arduino and ground
  {38, 43, 44, 41, 42, 39, 40, 45}, // LED pins connected to digital inputs 38-45 in arduino.and ground
  };

/**Declare the same first ENCODER.this time will be named "enc" */ 
CCRotaryEncoder enc = {
  
  {18, 19},                                // connected to digital pins 18 and 19 in arduino
  76,                                     // Midi CC signal
  speedMultiplier,                       // multiplier
  4,                                     // pulses per click
};

/**Next lines are for declare pedal on/off state LEDS..the leds reflects the pedal effect position
pedal buttons */ 
const pin_t ledPins[] = { 22, 23, 24, 25, 26, 27, 28, 29 };  //led pins connected to digital outputs 22-29 in arduino

template <class T, size_t N> constexpr size_t length(T (&)[N]) { return N; }

static_assert(length(pedalswitches) == length(ledPins),
              "Error: requires same number of buttons as LEDs");



void setup() {

    Control_Surface.begin();    // Control surface library init
    
 for (auto pin : ledPins)       //Set the pinMode to output for all LEDs
 
      pinMode(pin, OUTPUT);     
      
      pinMode(sw,INPUT_PULLUP);   //encoder pin(4) will be a digital input connected to digital 4 in arduino and with active pull-up resistor 
      
      pinMode(5,INPUT_PULLUP);     
      pinMode(6,INPUT_PULLUP);
      pinMode(7,INPUT_PULLUP);
      pinMode(14,INPUT_PULLUP);
      pinMode(15,INPUT_PULLUP);
      
      pinMode(mux2.pin(0),INPUT_PULLUP);
      pinMode(mux2.pin(1),INPUT_PULLUP);
      pinMode(mux2.pin(2),INPUT_PULLUP);
      pinMode(mux2.pin(3),INPUT_PULLUP);
      pinMode(mux2.pin(4),INPUT_PULLUP);
      pinMode(mux2.pin(5),INPUT_PULLUP);
      pinMode(mux2.pin(6),INPUT_PULLUP);
      pinMode(mux2.pin(7),INPUT_PULLUP);
      pinMode(mux2.pin(8),INPUT_PULLUP);
      pinMode(mux2.pin(9),INPUT_PULLUP);
      pinMode(mux2.pin(10),INPUT_PULLUP);
      pinMode(mux2.pin(11),INPUT_PULLUP);
      pinMode(mux2.pin(12),INPUT_PULLUP);
      pinMode(mux2.pin(13),INPUT_PULLUP);
      pinMode(mux2.pin(14),INPUT_PULLUP);
      pinMode(mux2.pin(15),INPUT_PULLUP);

      
  /* -- initializing the LCD.first simulate a old screen init,and then shows "inisio" and "esperarsus"  */
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
  lcd.print ("Inisio");
  delay(1000);
  lcd.setCursor (5,3);
  lcd.print ("Esperarsus");
  delay(800);
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
 




 

 
