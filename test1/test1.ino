#include <NewPing.h>
#include <DHT.h>
#include<SoftwareSerial.h>

#define TRIGGER_PIN  13
#define ECHO_PIN     12
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
SoftwareSerial miSerial(2,3);//Rx, Tx
DHT dht(9, 22);

int i, a=0, automovil = 0;
int valor1, valor2;

const byte pinVelocidad = 11; // terminal de la señal pwm del puente h
const byte pinVelocidad2 = 11;
const byte IN1pin = 4;
const byte IN2pin = 5; // terminales de entrada del puente h (para controlar el sentido de giro)
const byte IN3pin = 6;
const byte IN4pin = 7;

int POT = 100;

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
  Serial.begin(115200);
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
}

void loop() 
{
  valor1 = analogRead(A0);
    float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.println(h);
  Serial.print("Temperature: ");
  Serial.println(t);
  delay(1000);
  if(automovil == 0)
  {
    sonar.ping_cm();
    if(sonar.ping_cm()>13)
    {
      digitalWrite(IN1pin,LOW);
      digitalWrite(IN2pin,HIGH);
      digitalWrite(IN3pin,LOW);
      digitalWrite(IN4pin,HIGH);
    }
    else if(sonar.ping_cm()<12)
    {
      digitalWrite(IN1pin,LOW);
      digitalWrite(IN2pin,LOW);
      digitalWrite(IN3pin,LOW);
      digitalWrite(IN4pin,LOW);
    }
    else if(a == 1)
    {
      digitalWrite(IN1pin,HIGH);
      digitalWrite(IN2pin,LOW);
      digitalWrite(IN3pin,LOW);
      digitalWrite(IN4pin,LOW);
    }
    else
    {
      digitalWrite(IN1pin,LOW);
      digitalWrite(IN2pin,LOW);
      digitalWrite(IN3pin,LOW);
      digitalWrite(IN4pin,LOW);
    }
    analogWrite(pinVelocidad,POT);
    analogWrite(pinVelocidad2,POT);
  }
  if(automovil == 1)
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
    
