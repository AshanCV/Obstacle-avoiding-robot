#include <Servo.h>
Servo rotator;

#define servopin 6
#define trig 12
#define echo 11

#define LB 2  //left front
#define LF 3  //left back
#define RB 4  //right front
#define RF 5  //right back

int rotate_time=600; //time taken to rotate 45 degrees.

void setup() {
  //Serial.begin(9600);
  rotator.attach(servopin);
  rotator.write(90);


  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  
  
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  
  delay(1000);
}



void loop() {
  
if(getdistance()>15){
  forward();
}else{
  STOP();
  int rotate_to=SCAN();
  //Serial.println(rotate_to);
  if(rotate_to<0){
    rotateRight();
    //Serial.println("Right");
    delay(rotate_time);
    STOP();
  }else if(rotate_to>0){
    rotateLeft();
   // Serial.println("LEFT");
    delay(rotate_time);
    STOP();
  }else {
    rotateRight();
    //Serial.println("360");
    delay(2*rotate_time);
    STOP();
  }
}
}

int SCAN(){
  float distance,max_D=0;
  int max_D_angle=0;
 // Serial.print("distance ");
 // Serial.println(distance);
  
   for(int i=-1;i<2;i++){
    rotator.write(i*90+90);
    delay(300);
    distance=getdistance();
    //Serial.print(i);
   // Serial.print(" - ");
    //Serial.println(distance);
    delay(100);
    
    if(distance>max_D){
      max_D=distance;
      max_D_angle=i;
    }else{
      
    }
  }
  rotator.write(90);
  delay(200);
  //Serial.println(max_D);
 
  return max_D_angle;
}

void STOP(){
   digitalWrite(LF, LOW);
   digitalWrite(RF, LOW);       
   digitalWrite(LB, LOW);
   digitalWrite(RB, LOW);
}

void forward(){
   digitalWrite(LF, HIGH);
   digitalWrite(RF, HIGH);       
   digitalWrite(LB, LOW);
   digitalWrite(RB, LOW);
}

void backward(){
   digitalWrite(LF, LOW);
   digitalWrite(RF, LOW);       
   digitalWrite(LB, HIGH);
   digitalWrite(RB, HIGH);
}

void rotateRight(){
   digitalWrite(LF, HIGH);
   digitalWrite(RF, LOW);       
   digitalWrite(LB, LOW);
   digitalWrite(RB, HIGH);
}

void rotateLeft(){
   digitalWrite(LF, LOW);
   digitalWrite(RF, HIGH);       
   digitalWrite(LB, HIGH);
   digitalWrite(RB, LOW);
}


long getdistance() {

float T=0;
for(int i=0; i<5;i++){
 
 digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

long  t = pulseIn(echo, HIGH);
delay(0);
 T += t;
  
}
  T=T/5;
float D=T/29.1/2;

 if(D<=0){
  D=0;
 }
  return D;
}
