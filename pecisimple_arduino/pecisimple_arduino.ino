#include <Servo.h>

int enB = 7;
int In3 = 6;
int In4 = 5;
int data;
unsigned int sensor;
int batasNyala = 200;

Servo myServo1;
Servo myServo2;
Servo myServo3;

void setup() {
  Serial.begin(115200);
  myServo1.attach(11);
  myServo2.attach(9);
  myServo3.attach(10);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(enB, OUTPUT);

  myServo1.write(40);
  delay(100);
  myServo2.write(40);
  delay(100);
  myServo3.write(40);
  delay(100);
 
}

void loop(){
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  delay(1000);
//  digitalWrite(DeteksiPin, HIGH);
  sensor=analogRead(A1);
  
//  Serial.print("Nilai = ");
//  Serial.println(sensor);
//  delay(400);
  
  if(sensor<=batasNyala)
  {
//    digitalWrite(In3, LOW);
//    digitalWrite(In4, LOW);
  Serial.println("Ambil Data\n");
  delay(500);
  }
 
  while(Serial.available() !=0)
  {
    int data = Serial.read();
   
    Serial.flush();
    Serial.println(data);
    if (data == '1'){
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
    analogWrite(enB,100);
    }
    if (data == '2'){
     digitalWrite(In3, LOW);
     digitalWrite(In4, LOW);
     analogWrite(enB,0);
  }
  if (data == 4){
      
      myServo2.write(86);
      delay(100);
      myServo1.write(20);
      delay(100);
      myServo3.write(86);
      delay(100);
      digitalWrite(In3, HIGH);
      digitalWrite(In4, LOW);
      analogWrite(enB, 255);
      delay(7000);
      analogWrite(enB, 100);
      delay(1500);
  }
  
   if (data == 5){
      myServo1.write(20);
      delay(100);
      myServo2.write(20);
      delay(100);
      myServo3.write(86);
      delay(100);
      digitalWrite(In3, HIGH);
      digitalWrite(In4, LOW);
      analogWrite(enB, 255);
      delay(7000);
      analogWrite(enB, 100);
      delay(1500);
  }
   if (data == 6){
      myServo1.write(20);
      delay(100);
      myServo2.write(20);
      delay(100);
      myServo3.write(20);
      delay(100);
      digitalWrite(In3, HIGH);
      digitalWrite(In4, LOW);
      analogWrite(enB, 255);
      delay(7000);
      analogWrite(enB, 100);
      delay(1500);
   }
    if (data == 3){
      myServo1.write(30);
      delay(100);
      myServo2.write(30);
      delay(100);
      myServo3.write(30);
      delay(100);
      digitalWrite(In3, HIGH);
      digitalWrite(In4, LOW);
      analogWrite(enB, 255);
      delay(7000);
      analogWrite(enB, 100);
      delay(1500);
  }
  }
}
