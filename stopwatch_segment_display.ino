/*

  Real time stop watch displaying to 4 7-segment displays
  Uses two shift registers. One controls the 8 bits of the segments,
  and the second controls which segment is being displayed.
  The loop displays one digit at a time to each display.
  When the time interval has been reached, the timer count increases.

  On the first shift register, the 8 bits of data are wired to all
  4 displays. The second shift register then controls which display
  should be displayed with that number by enabling it's transistor
  to ground the display and complete the circuit.

  The circuit:
  - 2 shift registeres dasiy chained
  - 4 7-segment displays
  - 4 transistors controlling power to each display

  created 8 March 2018
  by Mitchell Sulkowski
  modified 8 Oct 2018
  by Mitchell Sulkowski

  https://github.com/electro2560/stopwatch-segment-display
*/

//yellow
int data_Pin = 10;
//blue
int clock_Pin = 9;
//purple
int latch_Pin = 8;

int numberToDisplay = 0;

//How many digits are being displayed
const int digits = 4;

//Which display should display the decimal point (1-digits)
const int decimal = 2;

int data[digits];

void setup() {
  pinMode(data_Pin, OUTPUT);
  pinMode(clock_Pin, OUTPUT);
  pinMode(latch_Pin, OUTPUT);

  numberToDisplay = 0000;

  recalculateDigits();
}

const unsigned long interval = (1000000 / 100) - 600;

unsigned long previousMicros = 0; //previous time of when the display was last incremented

void loop() {

  unsigned long currentMicros = micros(); //current time
  //check if the time has passed to increment to the next digit
  if (currentMicros - previousMicros >= interval) {
    previousMicros = micros();

    numberToDisplay++;

    //Reset the display back to zero when 99.99 seconds has passed
    if (numberToDisplay > 9999) numberToDisplay = 0;

  }

  recalculateDigits();

  for (int d = 0; d < digits; d++) {
    digitalWrite(latch_Pin, LOW);  // prepare shift register for data
    shiftOut(data_Pin, clock_Pin, LSBFIRST, B00010000 << d); // send data
    shiftOut(data_Pin, clock_Pin, LSBFIRST, numToBin(data[d]) + (d == decimal ? B00000001 : 0)); // send data
    digitalWrite(latch_Pin, HIGH); // update display
  }

}

void recalculateDigits() {

  for (int d = 0; d < digits; d++) {

    data[d] = (numberToDisplay / (int) pow(10, d)) % 10;

  }

}

/***************************************************************************************
     Title: SevenSegmentLEDdisplay102a.ino
     Author: Mel Lester Jr.
     Date: 2017-02-20
     Code version: <code version>
     Availability: https://www.hackster.io/meljr/7-segment-led-displays-102-using-a-shift-register-6b6976

***************************************************************************************/
byte numToBin(int someNumber) {
  switch (someNumber) {
    case 0:
      return B11111100;
      break;
    case 1:
      return B01100000;
      break;
    case 2:
      return B11011010;
      break;
    case 3:
      return B11110010;
      break;
    case 4:
      return B01100110;
      break;
    case 5:
      return B10110110;
      break;
    case 6:
      return B10111110;
      break;
    case 7:
      return B11100000;
      break;
    case 8:
      return B11111110;
      break;
    case 9:
      return B11110110;
      break;
    case 10:
      return B11101110; // Hexidecimal A
      break;
    case 11:
      return B00111110; // Hexidecimal B
      break;
    case 12:
      return B10011100; // Hexidecimal C or use for Centigrade
      break;
    case 13:
      return B01111010; // Hexidecimal D
      break;
    case 14:
      return B10011110; // Hexidecimal E
      break;
    case 15:
      return B10001110; // Hexidecimal F or use for Fahrenheit
      break;
    default:
      return B10010010; // Error condition, displays three vertical bars
      break;
  }

}
