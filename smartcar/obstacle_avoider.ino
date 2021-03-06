//ARDUINO OBSTACLE AVOIDING CAR//
// Before uploading the code you have to install the necessary library//
//AFMotor Library https://learn.adafruit.com/adafruit-motor-shield/library-install //
//NewPing Library https://github.com/livetronic/Arduino-NewPing// 
//Servo Library https://github.com/arduino-libraries/Servo.git //
// To Install the libraries go to sketch >> Include Library >> Add .ZIP File >> Select the Downloaded ZIP files From the Above links //


#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0   // Ultrasonic sensor
#define ECHO_PIN A1   // Ultrasonic sensor
#define MAX_DISTANCE 200 
#define MAX_SPEED 150 // This defines the the maximum speed of the car
#define MAX_SPEED_OFFSET 20

//Sensors 

int MID_IR = 16;   //A2 Pin
int RIGHT_IR = 17; //A3 Pin
int LEFT_IR = 18;  //A4 Pin

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ);   // Motor 1 and 2 have the same controls
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);   // Motor 3 and 4 have the same controls
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;                        // Servo control

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {

  myservo.attach(10);  
  myservo.write(85); 
  delay(2000);
  distance = readPing();
  delay(100);

  pinMode(MID_IR, INPUT); // initialize MID IR pin as input
  pinMode(LEFT_IR, INPUT); // initialize LEFT IR pin as an input
  pinMode(RIGHT_IR, INPUT); // initialize RIGHT IR pin as an input

  Serial.begin(9600);
  Serial.println();
  
}

void loop() {
 int distanceR = 0;
 int distanceL =  0;
// delay(40);
 int front = 0;

 if(digitalRead(LEFT_IR)!= 1)
 {
//    Serial.println("LEFT Senor detected and Onstacle");
    moveStop();
    turnRight();
    
 } else if(digitalRead(RIGHT_IR) != 1)
 {
//    Serial.println("RIGHT Senor detected and Onstacle");
    moveStop();
    turnLeft();
    
 }else if(digitalRead(MID_IR) != 1)
 { 
//    Serial.println("MID Senor detected and Onstacle");
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);
  
    if(distanceR>=distanceL)
    {
      turnRight();
      moveStop();
    }else
    {
      turnLeft();
      moveStop();
    }
    front = 1;
    
 }
 delay(40);
 moveForward();
 if(distance<=25 && front ==0)
 {
  front = 1;
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    turnRight();
    moveStop();
  }else
  {
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
}

int lookRight()
{
    myservo.write(0); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(85); 
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(85); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}  

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);     
  delay(400);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);      
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);  
  motor3.run(FORWARD);
  motor4.run(FORWARD);   
  delay(400);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}  
