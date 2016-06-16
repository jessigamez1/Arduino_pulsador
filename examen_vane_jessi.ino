#include <Servo.h>


int calibrationTime = 30;
long unsigned int pause = 5000;  
long unsigned int lowIn;
boolean lockLow = true;
boolean takeLowTime; 


int pirPin = 12; 
int pulsador1=6;
int pulsador2=7;
int led_rojo=5;
int led_verde=4;

int contador1=0;
int contador2=0;

Servo puerta;

void setup(){
      Serial.begin(9600);
      pinMode(pirPin, INPUT);
      pinMode(pulsador1,INPUT);
      pinMode(pulsador2,INPUT);
      pinMode(led_rojo,OUTPUT);
      pinMode(led_verde,OUTPUT);
      puerta.attach(9);
      puerta.write(0);
      
      digitalWrite(pirPin, LOW);
      Serial.print("calibrating sensor ");
      for(int i = 0; i < calibrationTime; i++){
        Serial.print(".");
        delay(1000);
        }
      Serial.println(" done");
      Serial.println("SENSOR ACTIVE");
      delay(50);
        
}

void loop(){
      
      
      if(digitalRead(pulsador1)==HIGH){
        contador1++;
        Serial.println(contador1);
        delay(1000);
      }

      if(digitalRead(pulsador2)==HIGH){
        contador2++;
        Serial.println(contador2);
        delay(1000);  
      }
      
      if(contador1==3 && contador2==2){
        digitalWrite(led_rojo,LOW);
        digitalWrite(led_verde,HIGH);
        puerta.write(180);
        contador1=0;
        contador2=0;
      }
      if(contador1==4 && contador2==3){
        digitalWrite(led_rojo,HIGH);
        digitalWrite(led_verde,LOW);
        puerta.write(0);
        contador1=0;
        contador2=0;
      }
  
   while(digitalRead(pirPin) == HIGH){
       digitalWrite(led_rojo, HIGH);   
       delay(100);
       digitalWrite(led_rojo, LOW);
       delay(100);
       digitalWrite(led_rojo, HIGH);
       if(lockLow){  
         lockLow = false;            
         delay(50);
         }         
         takeLowTime = true;
       }
       
       if(digitalRead(pirPin) == LOW){       
       digitalWrite(led_rojo, LOW);

       if(takeLowTime){
        lowIn = millis();          
        takeLowTime = false;       
        }
       if(!lockLow && millis() - lowIn > pause){  
           lockLow = true;                        
           delay(50);
           }
       }
  
  
}
