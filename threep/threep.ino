
int servoPin = 13;  // the servo is attached to IO_13 on the ESP32
int dutyCycle = 5;
const int servoFrequency = 50;  // 50Hz signal
const int servoChannel = 2;     // channels 0 and 1 are used for the two motors on your EEEBot
const int servoResolution = 12;  // 12-bit PWM signal

int steeringAngle = 180; // this value can be changed to vary the servo angle - only enter values between 0 and 180 degrees

void setup() {
  // put your setup code here, to run once:
  ledcSetup(servoChannel, servoFrequency, servoResolution); // servo setup on PWM channel 2, 50Hz, 12-bit (0-4095)
  ledcAttachPin(servoPin, servoChannel);  // attach the channel to the GPIO to be controlled

  // the purpose of the following line is to convert between the intuitive 'steering angle' value to the correct control signal for the servo
  dutyCycle = map((constrain(steeringAngle, 0, 180)), 0, 180, 205, 410); // contrain() limits the minimum and maximum values to 0 and 180 respectively, map() proportionally scales values between 0 and 180 to values between 205 (5% duty cycle) and 410 (10% duty cycle)

  ledcWrite(servoChannel, dutyCycle); // write the control signal to the PWM
}

void loop() {
  // put your main code here, to run repeatedly:
  // the code must be reuploaded each time the steering angle is changed - feel free to adapt this code to sweep between values if you wish
}
