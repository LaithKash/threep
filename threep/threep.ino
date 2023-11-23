#include <PID_v1.h>

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

ESP32Encoder encoder;

ESP32Encoder encoder2;



int64_t averageEncoders = (encoder.getCount()+encoder2.getCount())/2;

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
  encoder.attachHalfQuad(36,39); 

  encoder2.attachHalfQuad(34,35);

  encoder.clearCount();

  encoder2.clearCount();


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

  int64_t averageEncoders = (encoder.getCount()+encoder2.getCount())/2;
  
   // Set motor speed
   ledcWrite(pwmChannel, dutyCycle);

   
   float distanceNeeded = 286; //round(1 / distancePerRotation); 1 meter is 241 
   if((int64_t)averageEncoders <= distanceNeeded) {
     // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
     
     goForwards();
   } else {
     // Stop the DC motor
     Serial.println("Motor stopped");
   
     stopMotors();
   } 

     printf("The encoder count is %jd and enc1 is: %jd and enc2 is: %jd\n", averageEncoders, encoder.getCount(), encoder2.getCount());




}

   // Stop the DC motor