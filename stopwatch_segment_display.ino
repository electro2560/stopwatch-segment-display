
//yellow
int data_Pin = 10;
//blue
int clock_Pin = 9;
//purple
int latch_Pin = 8;

int numberToDisplay = 0;

//How many digits are being displayed
const int digits = 4;

int data[digits];

void setup() {
    pinMode(data_Pin, OUTPUT);
  pinMode(clock_Pin, OUTPUT);
  pinMode(latch_Pin, OUTPUT);

  numberToDisplay = 0000;

  recalculateDigits();
}


const int td = 1;

//const unsigned long interval = (1000 / 100) - 1;   // the time we need to wait
const unsigned long interval = (1000000 / 100) - 600;

unsigned long previousMillis = 0; // millis() returns an unsigned long.

void loop() {

  unsigned long currentMillis = micros(); // grab current time

  // check if "interval" time has passed to increment count
  if (currentMillis - previousMillis >= interval) {
    previousMillis = micros();

    numberToDisplay++;

    if (numberToDisplay > 9999) numberToDisplay = 0;

  }

  recalculateDigits();

  for (int d = 0; d < digits; d++) {
    digitalWrite(latch_Pin, LOW);  // prepare shift register for data
    shiftOut(data_Pin, clock_Pin, LSBFIRST, B00010000 << d); // send data
    shiftOut(data_Pin, clock_Pin, LSBFIRST, numToBin(data[d])); // send data
    digitalWrite(latch_Pin, HIGH); // update display
  }

  /*digitalWrite(latch_Pin, LOW);  // prepare shift register for data
    shiftOut(data_Pin, clock_Pin, LSBFIRST, B00010000); // send data
    shiftOut(data_Pin, clock_Pin, LSBFIRST, myfnNumToBits(data[0])); // send data
    digitalWrite(latch_Pin, HIGH); // update display

    //delay(td);

    digitalWrite(latch_Pin, LOW);  // prepare shift register for data
    shiftOut(data_Pin, clock_Pin, LSBFIRST, B00100000); // send data
    shiftOut(data_Pin, clock_Pin, LSBFIRST, myfnNumToBits(data[1])); // send data
    digitalWrite(latch_Pin, HIGH); // update display

    //delay(td);

    digitalWrite(latch_Pin, LOW);  // prepare shift register for data
    shiftOut(data_Pin, clock_Pin, LSBFIRST, B01000000); // send data
    shiftOut(data_Pin, clock_Pin, LSBFIRST, myfnNumToBits(data[2]) + B00000001); // send data
    digitalWrite(latch_Pin, HIGH); // update display

    //delay(td);

    digitalWrite(latch_Pin, LOW);  // prepare shift register for data
    shiftOut(data_Pin, clock_Pin, LSBFIRST, B10000000); // send data
    shiftOut(data_Pin, clock_Pin, LSBFIRST, myfnNumToBits(data[3])); // send data
    digitalWrite(latch_Pin, HIGH); // update display*/


  //delay(td);



  //Serial.print("end");
  // Serial.println(micros());


}

void recalculateDigits() {

  for (int d = 0; d < digits; d++) {

    // if(d == 0) data[d] = numberToDisplay % 10;
    // else data[d] = (numberToDisplay / (int) pow(10, d)) % 10;

    data[d] = (numberToDisplay / (int) pow(10, d)) % 10;

    //data[d] = (d == 0 ? numberToDisplay : (numberToDisplay / (10^d))) % 10;

  }

  //data[0] = numberToDisplay % 10;
  //data[1] = (numberToDisplay / 10) % 10;
  //data[2] = (numberToDisplay / 100) % 10;
  //data[3] = (numberToDisplay / 1000) % 10;
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
