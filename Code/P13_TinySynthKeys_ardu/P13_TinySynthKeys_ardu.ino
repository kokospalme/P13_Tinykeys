#include <CapacitiveSensor.h>
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523

#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
/*
 * Touchsensor sketch v1.0
 * (geändert von CapactiiveSensor library example sketch)
 * 
 * der Sender (pin 9) sendet ein Rechteck-Signal an den Empfänger (pin 10).
 * Der Widerstand (sehr hoch!) zwischen pin 9 und 10 lässt nur wenig Strom durch (I = U/R = 5V / 1000000 Ohm = 0,005 mA).
 * Wird die Leitung an pin 10 nicht berührt, kommt das Signal von pin 9 direkt an.
 * Wird die Leitung berührt, fließt kurz ein wenig Strom über den menschlichen Körper ab (ungefährlich).
 * Die Folge: der Strom fehlt kurzzeitig an pin 10, sodass das Signal erst später dort ankommt.
 * Der menschliche Körper "klaut" also kurzzeitig den Strom, was die "CapacitiveSensor" Bibliothek im Hintergrund für uns misst.
 * Da sich dieser Vorgang viele Male pro Sekunde wiederholt, messen wir den Vorgang nicht einmal, sondern 
 * 
 * 
 */


int pin_sig = 3;  //Variable des Typs int, für signal output-pin (SIG)
int pin_c1 = 8; //Variable des Typs int, für input-pin für Note C1
int pin_d = 9;  //Variable des Typs int, für input-pin für Note D 
int pin_e = 10; //Variable des Typs int, für input-pin für Note E
int pin_buzzer = 5; //Variable des Typs int, für output-pin für Buzzer

int durchlaeufe = 10;
int schwellwert = 50;

CapacitiveSensor   sensor_c1 = CapacitiveSensor(pin_sig,pin_c1); //sensor Objekt der Klasse "CapacitiveSensor" (für C1)
CapacitiveSensor   sensor_d = CapacitiveSensor(pin_sig,pin_d); //sensor Objekt der Klasse "CapacitiveSensor" (für D)
CapacitiveSensor   sensor_e = CapacitiveSensor(pin_sig,pin_e); //sensor Objekt der Klasse "CapacitiveSensor" (für E)

long sensorwert_c1, sensorwert_d, sensorwert_e, sensorwert_f, sensorwert_g, sensorwert_a, sensorwert_h, sensorwert_c2;  //Variablen des Typs "long", jeweils mit dem Namen "sensorwert..."

void setup()                    
{
   Serial.begin(115200);  //Serielle Kommunikation zwischen Arduino und Computer herstellen (Geschwindigkeit: 115200 BAUD)
   pinMode(pin_sig, OUTPUT);
   pinMode(pin_buzzer, OUTPUT);
}

void loop()                    
{
  sensorwert_c1 =  sensor_c1.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
  sensorwert_d =  sensor_d.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
  sensorwert_e =  sensor_e.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
  
  Serial.print(sensorwert_c1);Serial.print("\t");  // schicke "sensorwert"-Variable an Computer
  Serial.print(sensorwert_d);Serial.print("\t");
  Serial.println(sensorwert_e);

    if(sensorwert_c1 > schwellwert){
      tone(pin_buzzer, NOTE_C6);
      
    }else if(sensorwert_d > schwellwert){
      tone(pin_buzzer, NOTE_D6);
      
    } else if(sensorwert_e > schwellwert){
      tone(pin_buzzer, NOTE_E6);
      
    }else{
      noTone(pin_buzzer);
    }


    
    delay(10);  // warte 10 millisekunden 
}
