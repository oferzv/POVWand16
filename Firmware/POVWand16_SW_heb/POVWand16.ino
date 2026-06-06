// Code Example for JF jolliPOV Stick kit example Demo #1 Ver 1.0

// This Arduino sketch works with JF jolliPOV Stick handheld and waving it to and forth to display text and graphics
// For this example, set jumper to position B for text and graphics display using Main PCB's 16 LEDs
// Checkout instructable available at https://www.instructables.com/id/Arduino-Based-POV-Display-Stick-JolliPOV-Stick/

#define HEBFONT 0
#define ENGFONT 1


byte NumberBytesChar = 21;
#include "font.h"

// Define the Arduino LED pins in use
const byte LEDpins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}; // jolliPOV Stick Main PCB LED Pins

// Number of LEDs used
int LedCount() {
  return sizeof(LEDpins) / sizeof(*LEDpins);
}


// Define graphics 64 (Width) X 16 (Height)  ***********************************************************************************************************************
byte graphic[2][128] = {
  // Hearts 64 X 16
//  {
//    0x00, 0x00, 0xf0, 0x00, 0xf8, 0x01, 0x0c, 0x03, 0x06, 0x06, 0x06, 0x0c, 0x06, 0x18, 0x0c, 0x30, 0x18, 0x60, 0x0c, 0x30, 0x06, 0x18, 0x06, 0x0c, 0x06, 0x06, 0x0c, 0x03, 0xf8, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0xe0, 0x03, 0xf0, 0x07, 0xf0, 0x0f, 0xe0, 0x1f, 0xc0, 0x3f, 0xe0, 0x1f, 0xf0, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x08, 0x01, 0x04, 0x02, 0x02, 0x04, 0x02, 0x08, 0x02, 0x10, 0x04, 0x20, 0x08, 0x40, 0x04, 0x20, 0x02, 0x10, 0x02, 0x08, 0x02, 0x04, 0xf4, 0x02, 0xf8, 0x01, 0xfc, 0x03, 0xfe, 0x07, 0xfe, 0x0f, 0xfe, 0x1f, 0xfc, 0x3f, 0xf8, 0x7f, 0xfc, 0x3f, 0xfe, 0x1f, 0xfe, 0x0f, 0xfe, 0x07, 0xfc, 0x03, 0xf8, 0x01, 0xf0, 0x00, 0x00, 0x00
//  },

  // Arrows 64 x 16
  {
    0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xc0, 0x01, 0xf8, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xfe, 0x3f, 0xfc, 0x1f, 0xf8, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xf0, 0x07, 0xff, 0x7f, 0xfe, 0x3f, 0xfc, 0x1f, 0xf8, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00
  },

  {
    0x00, 0x00, 0x00, 0x00, 0xe4, 0x00, 0x02, 0x00, 0x02, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x08, 0x00, 0xe4, 0x03, 0x22, 0x00, 0x22, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0x82, 0x01, 0x42, 0x00, 0x4c, 0x00, 0x30, 0x00, 0x00, 0x00, 0x02, 0x01, 0x12, 0x01, 0xb2, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0xe4, 0x00, 0x02, 0x00, 0x02, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x08, 0x00, 0xe4, 0x03, 0x22, 0x00, 0x22, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x04, 0x00, 0x02, 0x00, 0x82, 0x01, 0x42, 0x00, 0x4c, 0x00, 0x30, 0x00, 0x00, 0x00, 0x02, 0x01, 0x12, 0x01, 0xb2, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

  
  }

  

};


const int NUMBER_OF_ELEMENTS = 6;

const char textString01 [] PROGMEM = "ARDIUNO - fqjafdya";
const char textString02 [] PROGMEM = "eqfyfxe jyha eay{q";
const char textString03 [] PROGMEM = "BRAVO!";
const char textString04 [] PROGMEM = "Hello";
const char textString05 [] PROGMEM = "WOW!";
const char textString06 [] PROGMEM = "Amazing";


struct message {
  char * text;
  byte fontType;
};

const message messages_new[NUMBER_OF_ELEMENTS] PROGMEM = {
  {textString01, HEBFONT},
  {textString02, HEBFONT},
  {textString03, ENGFONT},
  {textString04, ENGFONT},
  {textString05, ENGFONT},
  {textString06, ENGFONT}
};




unsigned long startTime = millis();
unsigned long elapsedTime = 30;     // 0.8 seconds lapse before re-triggering of display enabled

const byte triggerPin = 18;            //A4 connected to ball tilt switch
const int charDelay = 3000;          // Space between characters
const int tColDelay = 900;           // Space between text columns
const int gColDelay = 800;           // Space between graphic/pattern columns

byte textMsgSelection = 1;
byte graphicSelection = 1;
byte max_graphicCount = sizeof(graphic) / sizeof(graphic[0]);

boolean displayGraphics = false;
boolean firstByte = true;


int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

//****************************************************************************************************************************************************
void setup()
{


  Serial.begin(115200);
  for (int i = 0; i < LedCount(); i++) {
    pinMode(LEDpins[i], OUTPUT);
    digitalWrite(LEDpins[i], HIGH);
    delay(75);
    digitalWrite(LEDpins[i], LOW);
    delay(75);
  }

  for (int z=0; z<2; z++) {
    setPorts(255,255);
    delay(150);
    setPorts(0,0);
    delay(150);
    
  }
    
  pinMode(triggerPin, INPUT_PULLUP);

}

//****************************************************************************************************************************************************
void loop()
{

  // read the state of the switch into a local variable:
  int reading = digitalRead(triggerPin);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        setPorts(255, 255);

        if (displayGraphics == false)     // Display text messages
        {
          textMsgSelection++;

          if (textMsgSelection > NUMBER_OF_ELEMENTS)
          {
            textMsgSelection = 1;
            graphicSelection = 1;
            displayGraphics = true;
          }
        }
        else
        {
          graphicSelection++;

          if (graphicSelection > max_graphicCount)
          {
            textMsgSelection = 1;
            displayGraphics = false;
          }
        }
        delay(500);
        setPorts(0, 0);
      } // end if (buttonState == LOW)
    } //end if (reading != buttonState)
  } //end if

  lastButtonState = reading;

  if ((millis() - startTime) > elapsedTime)
  {
    if (displayGraphics == false)     // Display text messages
    {
      char * ptr = (char *) pgm_read_word (&messages_new[textMsgSelection - 1].text);
      char buffer [80];
      strcpy_P (buffer, ptr);
      byte fontType =  pgm_read_word (&messages_new[textMsgSelection - 1].fontType);


      for (int k = 0; k < strlen(buffer); k++) {
        if (fontType == HEBFONT)
          printLetterLarge(buffer[k], MyFontHeb);
        if (fontType == ENGFONT)
          printLetterLarge(buffer[k], MyFont);
      } //end for
    }
    else
    {
      firstByte = true;

      for (int k = 0; k < (sizeof(graphic) / max_graphicCount); k += 2)
      {
        setPorts(graphic[graphicSelection - 1][k], graphic[graphicSelection - 1][k + 1]);
        //ApplyGraphic(k);
        delayMicroseconds(gColDelay);
      }

    } //end if

    startTime = millis();
  } //end if elapsed time
}



//****************************************************************************************************************************************************
void printLetterLarge(char ch, unsigned short * font)
{
  // Make sure the character is within the alphabet bounds (defined by the font.h file)
  // If it's not, make it a blank character
  if (ch < 32 || ch > 126)
    ch = 32;

  // Step through each byte of the character array
  
  for (int i = 0; i < pgm_read_byte(&(font[((ch - 32) * NumberBytesChar)])); i++)
  {
    byte b = pgm_read_byte(&(font[((ch - 32) * NumberBytesChar) + 1 + (i * 2)]));
    byte b2 = pgm_read_byte(&(font[((ch - 32) * NumberBytesChar) + 2 + (i * 2)]));
    setPorts(b, b2);

    //    PORTD = (PORTD & B11) |  (b << 2);
    //    PORTB = b >> 6 | ((b2 & B1111) << 2);
    //    PORTC = (PORTC & B11110000) | b2 >> 4;

    // Space between columns
    delayMicroseconds(tColDelay);
  }

  // Clear LEDs
  setPorts(0, 0);
  //  PORTD = (PORTD & B11) ;
  //  PORTB = 0;
  //  PORTC = (PORTC & B11110000) ;

  // Space between characters
  delayMicroseconds(charDelay);
}

//***********************************************************************************************************************
void setPorts(byte data1, byte data2) {
  PORTD = (PORTD & B11) |  (data1 << 2);
  PORTB = data1 >> 6 | ((data2 & B1111) << 2);
  PORTC = (PORTC & B11110000) | data2 >> 4;
}


//***********************************************************************************************************************
int GraphicLength()
{
  return (sizeof(graphic[0]) / sizeof(*graphic[0]));
}


//***********************************************************************************************************************
void ApplyGraphic(int position)
{
  if (firstByte == true)
  {
    for (byte i = 0, bit = 1; i < 8; ++i, bit <<= 1)
    {
      firstByte = false;
      digitalWrite( LEDpins[i], (graphic[graphicSelection - 1][position]&bit) ? HIGH : LOW);
    }
  }
  else
  {
    for (byte i = 8, bit = 1; i < 16; ++i, bit <<= 1)
    {
      firstByte = true;
      digitalWrite( LEDpins[i], (graphic[graphicSelection - 1][position]&bit) ? HIGH : LOW);
    }
  }
}
