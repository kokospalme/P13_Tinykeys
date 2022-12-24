#include <CapacitiveSensor.h>
#include <synth.h>

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


#define TR_C1 0
#define TR_D 1
#define TR_E 2
#define TR_F 3
#define TR_G 4
#define TR_A 5
#define TR_H 5
#define TR_C2 5


synth synth;

int pin_sig1 = PD4;  //Variable des Typs int, für signal output-pin (SIG1)
int pin_c1 = 4; //Variable des Typs int, für input-pin für Note C1
int pin_f = 7;  //Variable des Typs int, für input-pin für Note D 

int pin_sig2 = PD3;//Variable des Typs int, für signal output-pin (SIG2)
int pin_d = 5;  //Variable des Typs int, für input-pin für Note D 
int pin_g = 8; //Variable des Typs int, für input-pin für Note G
int pin_h = 10; //Variable des Typs int, für input-pin für Note A


int pin_sig3 = PD3;//Variable des Typs int, für signal output-pin (SIG3)
int pin_e = 6; //Variable des Typs int, für input-pin für Note E
int pin_a = 9; //Variable des Typs int, für input-pin für Note A
int pin_c2 = 12; //Variable des Typs int, für input-pin für Note A

int pin_audio = PD5; //Variable des Typs int, für Audio output
int pin_led = PB5;  //Variable des Typs int, für LED output

int pin_poti1 = PD7;
int pin_poti2 = A6;
int pin_poti3 = A7;

int durchlaeufe = 10;
int schwellwert = 50;
unsigned long timer = 0;
uint8_t duration = 10;

CapacitiveSensor   sensor_c1 = CapacitiveSensor(pin_sig1,pin_c1); //sensor Objekt der Klasse "CapacitiveSensor" (für C1)
CapacitiveSensor   sensor_d = CapacitiveSensor(pin_sig2,pin_d); //sensor Objekt der Klasse "CapacitiveSensor" (für D)
CapacitiveSensor   sensor_e = CapacitiveSensor(pin_sig3,pin_e); //sensor Objekt der Klasse "CapacitiveSensor" (für E)
CapacitiveSensor   sensor_f = CapacitiveSensor(pin_sig1,pin_f); //sensor Objekt der Klasse "CapacitiveSensor" (für F)
CapacitiveSensor   sensor_g = CapacitiveSensor(pin_sig2,pin_g); //sensor Objekt der Klasse "CapacitiveSensor" (für G)
CapacitiveSensor   sensor_a = CapacitiveSensor(pin_sig3,pin_a); //sensor Objekt der Klasse "CapacitiveSensor" (für A)
CapacitiveSensor   sensor_h = CapacitiveSensor(pin_sig2,pin_h); //sensor Objekt der Klasse "CapacitiveSensor" (für A)
CapacitiveSensor   sensor_c2 = CapacitiveSensor(pin_sig3,pin_c2); //sensor Objekt der Klasse "CapacitiveSensor" (für A)


int voiceBusy[3] = {-1,-1,-1};  //-1 = free,

struct triggernote{
  long sensorwert = 0;
  int pin_no;
  int voice = -1; //-1 = not triggered
}

#ifdef __AVR_ATmega8__
#endif

triggernote[8];

void setup()                    
{
   //Serial.begin(115200);  //Serielle Kommunikation zwischen Arduino und Computer herstellen (Geschwindigkeit: 115200 BAUD)
   pinMode(pin_sig1, OUTPUT);
   pinMode(pin_sig2, OUTPUT);
   pinMode(pin_sig3, OUTPUT);
   pinMode(pin_led, OUTPUT);
   
   synth.begin(CHA);
   synth.setupVoice(0,SINE,60, ENVELOPE2,60,64);
   synth.setupVoice(1,SINE,60, ENVELOPE1,60,64);
   synth.setupVoice(2,SINE,60, ENVELOPE1,60,64);

}

void loop()                    
{


  if(millis() >= timer + duration){
    timer = millis() + duration;
      triggernote[TR_C1].sensorwert =  sensor_c1.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
  triggernote[1].sensorwert =  sensor_d.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
  triggernote[2].sensorwert =  sensor_e.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
  triggernote[3].sensorwert =  sensor_f.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
  triggernote[4].sensorwert =  sensor_g.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
  triggernote[5].sensorwert =  sensor_a.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
  
  //sensorwert_h =  sensor_h.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
  //sensorwert_c2 =  sensor_c2.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
  

    if(triggernote[TR_C1].sensorwert > schwellwert){
      int freeVoice = voiceIsFree();  //freeVoice?
      if(freeVoice >= 0){
        digitalWrite(pin_led,HIGH);
       // Serial.print("freevoice: ");Serial.println(freeVoice);
        triggernote[TR_C1].voice = freeVoice;
        synth.mTrigger(freeVoice, 60);  //trigger synth (c1)
        voiceBusy[freeVoice] = 1; //voice is now ocupied
      }
    }else{
      digitalWrite(pin_led,LOW);
      if(triggernote[TR_C1].voice >= 0){
       // Serial.println("free C1");
        synth.voiceFree(triggernote[TR_C1].voice);
        triggernote[TR_C1].voice = -1;
        voiceBusy[triggernote[TR_C1].voice] = -1;
      }
    }


    if(triggernote[TR_D].sensorwert > schwellwert){
      int freeVoice = voiceIsFree();  //freeVoice?
      if(freeVoice >= 0){
        digitalWrite(pin_led,HIGH);
        //Serial.print("freevoice: ");Serial.println(freeVoice);
        triggernote[TR_D].voice = freeVoice;
        voiceBusy[freeVoice] = TR_D; //voice is now ocupied from D
        synth.mTrigger(freeVoice, 62);  //trigger synth (c1)
      }else{
        //Serial.println("busy");
      }
    }else{
      digitalWrite(pin_led,LOW);
      if(triggernote[TR_D].voice >= 0){
       // Serial.println("free D");
        synth.voiceFree(triggernote[TR_D].voice);
        triggernote[TR_D].voice = -1;
        voiceBusy[triggernote[TR_D].voice] = triggernote[TR_D].voice;
      }
    }

    if(triggernote[TR_E].sensorwert > schwellwert){
      
      int freeVoice = voiceIsFree();  //freeVoice?
      if(freeVoice >= 0){
        digitalWrite(pin_led,HIGH);
        triggernote[TR_E].voice = freeVoice;
        voiceBusy[freeVoice] = TR_E; //voice is now ocupied from C1
        synth.mTrigger(freeVoice, 64);  //trigger synth (c1)
      }
    }else{
      digitalWrite(pin_led,LOW);
      if(triggernote[TR_E].voice >= 0){
        //Serial.println("free E");
        synth.voiceFree(triggernote[TR_E].voice);
        triggernote[TR_E].voice = -1;
        voiceBusy[triggernote[TR_E].voice] = triggernote[TR_E].voice;
      }
    }
  }


}

int voiceIsFree(){

  for(int i = 0; i < 3; i++){
    if(voiceBusy[i] >= 0){
      return i;
    }
  }
  return -1;
}

/*
 * 
 * Register: Atmega328 --> Atmega8
 * 
 * ?OCR2A --> 
 * ?OCR2B -->
 * ?TCCR1C -->
 * 
 */
