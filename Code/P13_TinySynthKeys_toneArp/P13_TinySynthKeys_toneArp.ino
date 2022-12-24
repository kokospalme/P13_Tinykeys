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


#define TR_C1 0
#define TR_D 1
#define TR_E 2
#define TR_F 3
#define TR_G 4
#define TR_A 5
#define TR_H 5
#define TR_C2 5


int pin_sig1 = 4;  //Variable des Typs int, für signal output-pin (SIG1)
int pin_c1 = 1; //Variable des Typs int, für input-pin für Note C1
int pin_f = 0;  //Variable des Typs int, für input-pin für Note D 

int pin_sig2 = 3;//Variable des Typs int, für signal output-pin (SIG2)
int pin_d = 19;  //Variable des Typs int, für input-pin für Note D 
int pin_g = 18; //Variable des Typs int, für input-pin für Note G
int pin_h = 17; //Variable des Typs int, für input-pin für Note A

int pin_sig3 = 2;//Variable des Typs int, für signal output-pin (SIG3)
int pin_e = 16; //Variable des Typs int, für input-pin für Note E
int pin_a = 15; //Variable des Typs int, für input-pin für Note A
int pin_c2 = 14; //Variable des Typs int, für input-pin für Note A

int pin_audio = 5; //Variable des Typs int, für Audio output
int pin_led = 13;  //Variable des Typs int, für LED output

int pin_poti1 = 7;  //ADC7
int pin_poti2 = A6;
int pin_poti3 = 7;

int pin_button2 = 9;  //PB1
int pin_button3 = 10; //PB2

int durchlaeufe = 50;
int schwellwert1 = 160;
int schwellwert2 = 160;
int schwellwert3 = 160;
unsigned long timer = 0;
uint8_t duration = 15;

CapacitiveSensor   sensor_c1 = CapacitiveSensor(pin_sig1,pin_c1); //sensor Objekt der Klasse "CapacitiveSensor" (für C1)
CapacitiveSensor   sensor_f = CapacitiveSensor(pin_sig1,pin_f); //sensor Objekt der Klasse "CapacitiveSensor" (für F)

CapacitiveSensor   sensor_d = CapacitiveSensor(pin_sig2,pin_d); //sensor Objekt der Klasse "CapacitiveSensor" (für D)
CapacitiveSensor   sensor_g = CapacitiveSensor(pin_sig2,pin_g); //sensor Objekt der Klasse "CapacitiveSensor" (für G)
CapacitiveSensor   sensor_h = CapacitiveSensor(pin_sig2,pin_h); //sensor Objekt der Klasse "CapacitiveSensor" (für A)

CapacitiveSensor   sensor_e = CapacitiveSensor(pin_sig3,pin_e); //sensor Objekt der Klasse "CapacitiveSensor" (für E)
CapacitiveSensor   sensor_a = CapacitiveSensor(pin_sig3,pin_a); //sensor Objekt der Klasse "CapacitiveSensor" (für A)
CapacitiveSensor   sensor_c2 = CapacitiveSensor(pin_sig3,pin_c2); //sensor Objekt der Klasse "CapacitiveSensor" (für A)

int voiceBusy[3] = {-1,-1,-1};  //-1 = free,

struct triggernote{
  long sensorwert = 0;
  int pin_no;
  int voice = -1; //-1 = not triggered
  bool gedrueckt = false;
  uint16_t note = 0;
}

triggernote[8];
int noteOffset = 0;

unsigned long arpTimer = 0;
uint16_t bpm = 128; //bpm 50...500 bpm
uint16_t speedValue = 0;
bool arpOn = false;  //arpeggiator on
uint8_t arpMode = 0;
uint8_t sustain = 20; //20...2000 ms
uint16_t arpNotes[5] = {0,0,0,0,0};
uint8_t arpAmmount = 0;
uint8_t arpCounter = 0;
bool arpHold = false;

bool _gedrueckt;

void setup()                    
{
   //Serial.begin(115200);  //Serielle Kommunikation zwischen Arduino und Computer herstellen (Geschwindigkeit: 115200 BAUD)
   pinMode(pin_sig1, OUTPUT);
   pinMode(pin_sig2, OUTPUT);
   pinMode(pin_sig3, OUTPUT);
   pinMode(pin_led, OUTPUT);

}


void loop()                    
{

  if(millis() >= timer + duration){
    timer = millis() + duration;

    if(!digitalRead(pin_button2) && arpOn){
      delay(50);
      if(digitalRead(pin_button2))return;//too short
      arpHold =!arpHold;
      digitalWrite(pin_led,HIGH);
      delay(10);
      digitalWrite(pin_led,LOW);
    }

    if(!digitalRead(pin_button2) && !digitalRead(pin_button3)){
      arpTimer = millis();
      while(!digitalRead(pin_button2) || !digitalRead(pin_button3)){ 
        digitalWrite(pin_led,LOW);

        if(millis() > arpTimer + 1000){ //long press
          digitalWrite(pin_led,HIGH);
          delay(50);
          digitalWrite(pin_led,LOW);
          arpOn = !arpOn;
          if(arpOn) arpMode = 0;
          return;
        }
      }
      delay(10);
    }
    
    triggernote[0].sensorwert =  sensor_c1.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[1].sensorwert =  sensor_d.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[2].sensorwert =  sensor_e.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[3].sensorwert =  sensor_f.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[4].sensorwert =  sensor_g.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[5].sensorwert =  sensor_a.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[6].sensorwert =  sensor_h.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[7].sensorwert =  sensor_c2.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 

    
    if(triggernote[0].sensorwert >= schwellwert1){
      triggernote[0].gedrueckt = true;
      triggernote[0].note = NOTE_C4;
      if(!arpOn){
        tone(pin_audio, triggernote[0].note);
      }
    }else{
      triggernote[0].gedrueckt = false;
    }
    
    if(triggernote[1].sensorwert >= schwellwert2){
      triggernote[1].gedrueckt = true;
      triggernote[1].note = NOTE_D4;
      if(!arpOn){
        tone(pin_audio, triggernote[1].note);
      }  
    }else{
      triggernote[1].gedrueckt = false;
    }

     if(triggernote[2].sensorwert >= schwellwert3){
      triggernote[2].gedrueckt = true;
      triggernote[2].note = NOTE_E4;
      if(!arpOn){
        tone(pin_audio, NOTE_E4);
      }
    }else{
      triggernote[2].gedrueckt = false;
    }
    
     if(triggernote[3].sensorwert >= schwellwert1){
      triggernote[3].gedrueckt = true;
      triggernote[3].note = NOTE_F4 + noteOffset;
      if(!arpOn){
        tone(pin_audio, NOTE_F4);
      }
    }else{
      triggernote[3].gedrueckt = false;
    }

    if(triggernote[4].sensorwert >= schwellwert2){
      triggernote[4].gedrueckt = true;
      triggernote[4].note = NOTE_G4 + noteOffset;
      if(!arpOn){
        tone(pin_audio, NOTE_G4);
      }
    }else{
      triggernote[4].gedrueckt = false;
    }
    
    if(triggernote[5].sensorwert >= schwellwert3){
      triggernote[5].gedrueckt = true;
      triggernote[5].note = NOTE_A4 + noteOffset;
      if(!arpOn){
         tone(pin_audio, NOTE_A4);
      }
    }else{
      triggernote[5].gedrueckt = false;
    }
    
    if(triggernote[6].sensorwert >= schwellwert2){
      triggernote[6].gedrueckt = true;
      triggernote[6].note = NOTE_B4 + noteOffset;
      if(!arpOn){
        tone(pin_audio, NOTE_B4);
      }
    }else{
      triggernote[6].gedrueckt = false;
    }
    
    if(triggernote[7].sensorwert >= schwellwert3){
      triggernote[7].gedrueckt = true;
      triggernote[7].note = NOTE_C5 + noteOffset;
      if(!arpOn){
        tone(pin_audio, NOTE_C5);
      }
    }else{
      
      triggernote[7].gedrueckt = false;
    }

    if(arpOn){
      
      if(arpHold){  //arp on hold

      }else{  //arp not hold

        arpAmmount = 0; //clear arp when not on hold
        for(int i = 0; i < 8;i++){
          if(triggernote[i].gedrueckt){
           arpNotes[arpAmmount] =  triggernote[i].note;
          arpAmmount++;
         }
        if(arpAmmount >= 5) return; //wenn 5 noten voll: return!
        }
        
      }

      
     _gedrueckt = false;
     
     for(int i = 0; i < 8;i++){
      if(triggernote[i].gedrueckt){
        _gedrueckt = true;
      }
     }
      
    }else{
      
     _gedrueckt = false;
     
     for(int i = 0; i < 8;i++){
      if(triggernote[i].gedrueckt){
        _gedrueckt = true;
      }
     }
     
     if(!_gedrueckt){ //stop wenn nichts gedrückt
        noTone(pin_audio);
        digitalWrite(pin_led, LOW);
      }else{
        digitalWrite(pin_led, HIGH);
      }
    }

  }

    uint32_t _sum = 0;
    for(int i = 0; i < 20;i++){
      _sum += map(analogRead(pin_poti2),0,1023,50,500);
    }
    _sum /=20;
    bpm = (uint16_t) _sum;
    
    sustain = map(analogRead(pin_poti3),0,1023,2,2000);



    if(arpOn){
      uint16_t arpMillis = 60000/bpm;
  
      if(millis() > arpTimer + arpMillis ){
      arpTimer = millis();
      digitalWrite(pin_led, HIGH);
      if(_gedrueckt || arpHold){
              switch(arpMode){
        case 0:
        tone(pin_audio,arpNotes[arpCounter], sustain);
        arpCounter++;
        if(arpCounter >= arpAmmount){
          arpCounter = 0;
        }
        break;
        /*
        case 1: //down
        tone(pin_audio,arpNotes[arpCounter], sustain);
        arpCounter--;
        if(arpCounter <= 0){
          arpCounter = arpAmmount-1;
        }
        break;
        case 2: //random
        tone(pin_audio,arpNotes[random(0,arpAmmount-1)], sustain);
        break;
        */
        
      }




        
      }

    
    digitalWrite(pin_led, LOW);
    }
  }



}
