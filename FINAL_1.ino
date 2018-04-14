#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
Servo myservo; 
int gaslevel,val; 
#define L 13
#define B 7
void setup() {
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    
  myservo.attach(6);
  pinMode(A5,INPUT);
  pinMode(L,OUTPUT);
  pinMode(B,OUTPUT);

}


void loop() {
  
  gaslevel=analogRead(A5);
  Serial.println(analogRead(A5));
  
  if(gaslevel >= 350 )
  {      SendMessage();     
         digitalWrite(L,HIGH);//red led is on
         digitalWrite(B,HIGH);//buzzer is on
         myservo.write(180);
         delay(100);  
    
  }
  else
  {      digitalWrite(L,LOW);//red led is off
         digitalWrite(B,LOW);//buzzer is off
         myservo.write(0);
         delay(100);  
   }

}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919028095540\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Fire Alert !! ");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
