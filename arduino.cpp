// C++ code
// 
/* I could not produce orange and yellow light.
For that I needed an analog output pin and I utilised
all of those for the motors. */ 

#include<Servo.h>
int dirPin1 = 13; 
int dirPin2 = 12; 
int speedPinFL = 11;
int speedPinFR = 10; 
int speedPinBR = 9; 
int speedPinBL = 6;
int radius = 5; 
int servoPin = 3; 
int delayT = 0;
Servo myServo; 
int buzzerPin = 4;  
int redPin =8; 
int bluePin=7;
int greenPin =5;
int distance; 

void setup()
{
  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT); 
  pinMode(speedPinFL, OUTPUT);
  pinMode(speedPinFR, OUTPUT);
  pinMode(speedPinBL, OUTPUT);
  pinMode(speedPinBR, OUTPUT);
  pinMode(buzzerPin, OUTPUT); 
  pinMode(redPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 
  pinMode(greenPin, OUTPUT);
 
  myServo.attach(servoPin); 
}  

/* Since the sound produced by PCB increases as the mine
approaches closer, we can estimate the distance using a sound
sensor and input it into the code*/

void Buzzer(int distance)
{
  if(distance>3)
  {
    digitalWrite(buzzerPin,HIGH); 
    delay(600);
    digitalWrite(buzzerPin, LOW);
    delay(1000); 
    digitalWrite(greenPin, HIGH);
    //Set all the other Pins to low 
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin, LOW);
  }
  if(distance<3)
  {
    digitalWrite(buzzerPin, HIGH); 
    delay(500); 
    digitalWrite(buzzerPin,LOW);
    delay(500);
    digitalWrite(bluePin, HIGH); 
    //Set all the other Pins to low 
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin, LOW);
  } 
  if(distance==0)
  {
    digitalWrite(buzzerPin, HIGH); 
    digitalWrite(redPin, HIGH);
   
    //Set all the other Pins to low 
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }  
  if(distance==-1) // This is if the soil is being dug up
  {
    igitalWrite(buzzerPin, LOW); 
    digitalWrite(redPin, LOW);
    //Set all the other Pins to low 
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
    
}
/*Instead of using differential drive, I have used car-like 
control. I have attached the image of the mechanism in the repo.
For this function steerToAngle(), we take 2 inputs phi and omega.
The servo motor reaches the angle phi at the rate described by 
omega(w) */
void steerToAngle(int phi, int w)
{
  int delayT = 0; 
  int servoAngle = 0;
  while(delayT!=(phi/w))
  {
    servoAngle+=w;
    delayT +=1;
    delay(1000);
    myServo.write(servoAngle);
  } 
  
} 
/* 16530 rpm is the max rpm of the motors. We get angular 
velocity by w = v1/r and linear interpolate betweem (0,0)
(16530,255) to get a wheel velocity */


void wheelVelocity(float v1, float radius)
{ 
  //Since wheels are in pure rolling, v1 = wr
  float w = v1/radius;
  float rpm = w * (30/3.14); 
  float wheelV = 0.01539154 * rpm; 
  analogWrite(speedPinFL, wheelV); 
  analogWrite(speedPinFR, wheelV); 
  analogWrite(speedPinBL, wheelV);
  analogWrite(speedPinBR, wheelV);
  
}


  

void loop()
{ 
  int distance = 5 ; 
  int phi = 40; 
  int w = 5; 
  int v1 = 40; 
  int radius = 5;
  digitalWrite(dirPin1, HIGH);
  digitalWrite(dirPin2, LOW);
  Buzzer(distance);
  steerToAngle(phi,w);
  wheelVelocity(v1,radius); 
  delay(5000);
}
