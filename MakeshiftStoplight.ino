//Created by Brandon Contino
//Last Modified 12/25/2014
//Program emulates a makeshift stoplight controlled by a light sensor to 
//signify when a car arrives. Adds in a faded yellow light and red light 
//capability.
#include <avr/io.h>
#include <avr/interrupt.h>

int photopin = A0;
int redPin = 6;
int yellowPin = 5;
int greenPin = 3;
int photoval;
int pval;


void setup()
{
  Serial.begin(9600);
  pinMode(photopin,INPUT);
  pinMode(redPin,OUTPUT);
  pinMode(yellowPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  // initialize Timer1
    cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B
 
    // set compare match register to desired timer count:
    OCR1A = 15624;
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    // enable global interrupts:
    sei();
}

void loop()
{
    digitalWrite(greenPin,LOW);
    digitalWrite(redPin,HIGH);
    digitalWrite(yellowPin,LOW);
    delay(5000);
  if (pval < -10)
  {
    for(int ii = 255; ii >= 0; ii = ii - 20)
    {
      analogWrite(redPin,ii);
      delay(100);
    }
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,HIGH);
    delay(5000);
    digitalWrite(greenPin,LOW);
    digitalWrite(yellowPin,HIGH);
   for(int ii = 255; ii >= 0; ii = ii - 10)
    {
      analogWrite(yellowPin,ii);
      delay(100);
    }
    digitalWrite(yellowPin,LOW);
    digitalWrite(redPin,HIGH);
  }
}

ISR(TIMER1_COMPA_vect)
{
  photoval = analogRead(photopin);
  pval = photoval - 494;
  Serial.println(pval);
  Serial.println();
}

