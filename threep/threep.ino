

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

//#########################################################################################################################################################################################################################################################################
int servoPin = 13;  // the servo is attached to IO_13 on the ESP32
int dutyCycle_servo = 5;
const int servoFrequency = 50;  // 50Hz signal
const int servoChannel = 2;     // channels 0 and 1 are used for the two motors on your EEEBot
const int servoResolution = 12;  // 12-bit PWM signal

int steeringAngle = 90; // this value can be changed to vary the servo angle - only enter values between 0 and 180 degrees

void setup() {

//#########################################################################################################################################################################################################################################################################
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


//#########################################################################################################################################################################################################################################################################
  // put your setup code here, to run once:
  ledcSetup(servoChannel, servoFrequency, servoResolution); // servo setup on PWM channel 2, 50Hz, 12-bit (0-4095)
  ledcAttachPin(servoPin, servoChannel);  // attach the channel to the GPIO to be controlled

  // the purpose of the following line is to convert between the intuitive 'steering angle' value to the correct control signal for the servo
  steeringAngle = map((constrain(steeringAngle, 0, 180)), 0, 180, 205, 410); // contrain() limits the minimum and maximum values to 0 and 180 respectively, map() proportionally scales values between 0 and 180 to values between 205 (5% duty cycle) and 410 (10% duty cycle)

  ledcWrite(servoChannel, abs(steeringAngle)); // write the control signal to the PWM
//#########################################################################################################################################################################################################################################################################




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
delay(100);
    float steeringAngle = 180;
    delay(100);

    ledcWrite(servoChannel, abs(steeringAngle)); // write the control signal to the PWM

     goForwards();

     Serial.println("Moving Forward");

     printf("The encoder count is %jd and enc1 is: %jd and enc2 is: %jd\n", averageEncoders, encoder.getCount(), encoder2.getCount());


  
     } 
    else if((int64_t)averageEncoders >= 50, (int64_t)averageEncoders <= 100) {
     
     float steeringAngle = 0;

     delay(100);
    ledcWrite(servoChannel, abs(steeringAngle)); // write the control signal to the PWM
    // stopMotors();

    //      Serial.println("Motors stopped");
      
      delay(500);
      
      goBackwards();

          Serial.println("Moving backwards");
   } 


  else{
      delay(500);
     // stopMotors();
       Serial.println("Motors stopped");


      


      //go forwards
    }

}
 


   // Stop the DC motor