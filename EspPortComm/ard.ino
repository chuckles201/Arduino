// setting up IR receiver
// downloading module
#include <IRremote.h>

#include <Servo.h>

// commands
const String OK = "3576350698";
const String PWR = "3893872618";
const String UP = "1721354218";
const String DOWN = "1286850538";
const String RIGHT = "1387120618";
const String LEFT = "1637795818";

const int whitePin = 2;



// digital pin to receive
// the IR info
IRrecv IR(3);

Servo servoBottom;
Servo servoTop;

// connect to gd and 5 volts, and then 
// constantly monitor

void setup() {
  // receiver enable
  IR.enableIRIn();
  Serial.begin(9600);

  // attaching bottom/top
  servoBottom.attach(10);
  servoTop.attach(11);

  pinMode(whitePin,OUTPUT);

}

String irData;

int servoPosTop = 90;
int servoPosBot = 90;


bool laserOn = false;

void loop() {
  // check to detect
  if (IR.decode()) {
    // printing raw IR reception! (same thing)
    irData = String(IR.decodedIRData.decodedRawData);

    // Serial.print("RAW: ");
    // Serial.println(irData);

    if (irData == UP){
      if (servoPosTop > 1)
      servoPosTop -= 4;
    }
    else if (irData == DOWN){
      if (servoPosTop < 179){
      servoPosTop += 4;
    }
    }
    else if (irData == LEFT){
      if (servoPosBot > 1){
      servoPosBot -= 4;
    }
    }
    else if (irData == RIGHT){
      if (servoPosBot < 179){
      servoPosBot += 4;
    }

    // ON/OFF LASER
    // LED to display
    else if (irData == PWR){
      if (laserOn){
        digitalWrite(whitePin,LOW);
        laserOn = false;
      }
      else {
        digitalWrite(whitePin,HIGH);
        laserOn = true;
      }
    }
    }

    // continue looking for IR signals
    delay(5);
    IR.resume();
  }

  // write changes
  servoTop.write(servoPosTop);
  servoBottom.write(servoPosBot);
  // Check for serial data from ESP32
if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    // Process the received data here
    Serial.println("Received: " + data);

    for (int i = 0; i < data.length();i++){
      char c = data.charAt(i);
      if (c == '0') {
        servoPosTop -= 4;
      }
      else if (c == '1') {
        servoPosTop += 4;
      }
      else if (c == '2') {
        servoPosBot -= 4;
      }
      else if (c == '3') {
        servoPosBot += 4;
      }
      else if (c == 't') {
        if (laserOn){
          digitalWrite(whitePin,LOW);
          laserOn = false;
        }
        else {
          digitalWrite(whitePin,HIGH);
          laserOn = true;
      }
      }
    }
}
  
}
