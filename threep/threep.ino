

#include <ESP32Encoder.h>

#define enA 33  //EnableA command line
#define enB 25  //EnableA command line

#define INa 26  //Channel A Direction
#define INb 27  //Channel A Direction
#define INc 14  //Channel B Direction
#define INd 12  //Channel B Direction


const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 255;


void setup() {
  // sets the pins as outputs:
  pinMode(INa, OUTPUT);
  pinMode(INb, OUTPUT);
  pinMode(INc, OUTPUT);
  pinMode(INd, OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enA, pwmChannel);
  
  ledcAttachPin(enB, pwmChannel);

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");

  // attach encoder to pins



}

void goForwards() {
    digitalWrite(INa, HIGH);
    digitalWrite(INb, LOW);
    digitalWrite(INc, HIGH);
    digitalWrite(INd, LOW);
}

void stopMotors() {
    digitalWrite(INa, LOW);
    digitalWrite(INb, LOW);
    digitalWrite(INc, LOW);
    digitalWrite(INd, LOW);
}

void goBackwards() {
    digitalWrite(INa, LOW);
    digitalWrite(INb, HIGH);
    digitalWrite(INc, LOW);
    digitalWrite(INd, HIGH);
}



void loop() {

  
   // Set motor speed
   ledcWrite(pwmChannel, dutyCycle);

   
  goForwards();

  delay(3000);

  goBackwards();

  delay(3000);

  goForwards();

  delay(3000);

  stopMotors();

  delay(30000);








}

   // Stop the DC motor