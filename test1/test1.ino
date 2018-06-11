#include <NewPing.h>
#include <DHT.h>
#include<SoftwareSerial.h>

#define TRIGGER_PIN  13
#define ECHO_PIN     12
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
SoftwareSerial miSerial(2,3);//Rx, Tx
DHT dht(9, 22);

char Nombre[21]= "HC-06 Andrea";
char BPS = '4'; //1 = 1200, 2= 2400, 3 = 4800, 4= 9600, 5= 19200, 6=38400
char password[5]= "6952";

int i, a=0, automovil = 0;
int valor1, valor2;

const byte pinVelocidad = 11; // terminal de la señal pwm del puente h
const byte pinVelocidad2 = 11;
const byte IN1pin = 4;
const byte IN2pin = 5; // terminales de entrada del puente h (para controlar el sentido de giro)
const byte IN3pin = 6;
const byte IN4pin = 7;

int POT = 80;

void pausa()
{
  if(a == 2)
  {
    digitalWrite(IN1pin,LOW);
    digitalWrite(IN2pin,LOW);
    digitalWrite(IN3pin,LOW);
    digitalWrite(IN4pin,LOW);
  }
}

void setup() 
{
  Serial.begin(9600);
  miSerial.begin(9600);
  pinMode(IN1pin,OUTPUT);
  pinMode(IN2pin,OUTPUT);
  pinMode(pinVelocidad,OUTPUT);
  pinMode(pinVelocidad2,OUTPUT);
  pinMode(IN3pin,OUTPUT);
  pinMode(IN4pin,OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A0, INPUT);
  dht.begin();
  miSerial.print("AT");
  miSerial.print("AT+BAUD");
  miSerial.print(BPS);
  miSerial.print("AT+NAME");
  miSerial.print(Nombre);
  miSerial.print("AT+PIN");
  miSerial.print(password);
}

void loop() 
{
  valor1 = analogRead(A0);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  //Serial.print("Humidity: ");
  //Serial.println(h);
  //Serial.print("Temperature: ");
  //Serial.println(t);
  if(miSerial.available())
  {
    String c = miSerial.readString();
    int b = c[0];
    Serial.println(c);
  if(automovil == 0)
  {
    sonar.ping_cm();
    if(b == '1')
    {
      digitalWrite(IN1pin,HIGH);
      digitalWrite(IN2pin,LOW);
      digitalWrite(IN3pin,HIGH);
      digitalWrite(IN4pin,LOW);
    }
    else if(b == '0')
    {
      digitalWrite(IN1pin,LOW);
      digitalWrite(IN2pin,LOW);
      digitalWrite(IN3pin,LOW);
      digitalWrite(IN4pin,LOW);
    }
    else if(b == '2')
    {
      digitalWrite(IN1pin,HIGH);
      digitalWrite(IN2pin,LOW);
      digitalWrite(IN3pin,LOW);
      digitalWrite(IN4pin,LOW);
    }
    else if(b == '3')
    {
      digitalWrite(IN1pin,LOW);
      digitalWrite(IN2pin,LOW);
      digitalWrite(IN3pin,HIGH);
      digitalWrite(IN4pin,LOW);
    }
    else if(b == '4')
    {
      digitalWrite(IN1pin,LOW);
      digitalWrite(IN2pin,HIGH);
      digitalWrite(IN3pin,LOW);
      digitalWrite(IN4pin,HIGH);      
    }
    analogWrite(pinVelocidad,POT);
    analogWrite(pinVelocidad2,POT);
  if(b == '9')
  {
    valor1 = analogRead(A0);
    valor2 = analogRead(1);
    if(valor1 < 1000 && valor2 > 7)
    { 
      digitalWrite(IN1pin,HIGH);
      digitalWrite(IN2pin,LOW);
      digitalWrite(IN3pin,HIGH);
      digitalWrite(IN4pin,LOW);
    }
    else if(valor1 < 1000 && valor2 > 7)
    { 
      digitalWrite(IN1pin,LOW);
      digitalWrite(IN2pin,LOW);
      digitalWrite(IN3pin,HIGH);
      digitalWrite(IN4pin,LOW);
    }
    else if(valor1 < 1000 && valor2 > 7)
    { 
      digitalWrite(IN1pin,HIGH);
      digitalWrite(IN2pin,LOW);
      digitalWrite(IN3pin,LOW);
      digitalWrite(IN4pin,LOW);
    }
  }
  }
  }
}
