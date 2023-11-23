

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
int dutyCycle = 180;

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

void goBackwards() {
    digitalWrite(INa, LOW);
    digitalWrite(INb, HIGH);
    digitalWrite(INc, LOW);
    digitalWrite(INd, HIGH);
}

void stopMotors() {
    digitalWrite(INa, LOW);
    digitalWrite(INb, LOW);
    digitalWrite(INc, LOW);
    digitalWrite(INd, LOW);
}



void loop() {

  int64_t averageEncoders = (encoder.getCount()+encoder2.getCount())/2;
  
   // Set motor speed
   ledcWrite(pwmChannel, dutyCycle);

   
   //float distanceNeeded = 286; //round(1 / distancePerRotation); 1 meter is 241 
    if((int64_t)averageEncoders <= 50) {
     // Move the DC motor forward at maximum speed

     goForwards();

     Serial.println("Moving Forward");

     printf("The encoder count is %jd and enc1 is: %jd and enc2 is: %jd\n", averageEncoders, encoder.getCount(), encoder2.getCount());

  
     } 
    else if((int64_t)averageEncoders >= 50, (int64_t)averageEncoders <= 100) {
     
    // stopMotors();

    //      Serial.println("Motors stopped");
      
      delay(500);
      
      goBackwards();

          Serial.println("Moving backwards");
   } 
    /*else{
      
      stopMotors();
       Serial.println("Motors stopped");


      delay(500);

      goForwards();

     Serial.println("Moving Forward");

      //go forwards
    }*/

     




}

   // Stop the DC motor