#include <CapacitiveSensor.h> //füge Bibliothek "CapacitiveSensor" hinzu

// Noten
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
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
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
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

int noten[49] = {NOTE_C3, NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3, NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3, NOTE_B3,  //Notenarray
                    NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
                    NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
                    NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
                    NOTE_C7
                  };
int oktave = 0;

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

int pin_poti1 = A1;
int pin_sw2 = 9;  //PB1
int pin_sw3 = 10;  // PB2

int durchlaeufe = 50;
int schwellwert1 = 150;
int schwellwert2 = 150;
int schwellwert3 = 150;
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
}

triggernote[8];

void setup()                    
{
  pinMode(pin_sig1, OUTPUT);
  pinMode(pin_sig2, OUTPUT);
  pinMode(pin_sig3, OUTPUT);
  pinMode(pin_led, OUTPUT);
  pinMode(pin_sw2, INPUT);
  pinMode(pin_sw2, INPUT);
}


void loop()                    
{
  bool gedrueckt = false;

  if(millis() >= timer + duration){
    timer = millis() + duration;
    
    triggernote[0].sensorwert =  sensor_c1.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[1].sensorwert =  sensor_d.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[2].sensorwert =  sensor_e.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[3].sensorwert =  sensor_f.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[4].sensorwert =  sensor_g.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[5].sensorwert =  sensor_a.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[6].sensorwert =  sensor_h.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 
    triggernote[7].sensorwert =  sensor_c2.capacitiveSensor(durchlaeufe);  //sensorwert gespeichert, der von der Funktion "capacitiveSensor" des Objekts "sensor" ausgegeben wird 

    if(triggernote[0].sensorwert >= schwellwert1){
      tone(pin_audio, noten[oktave * 12 + 0]);
      gedrueckt = true;
    }
    
    if(triggernote[1].sensorwert >= schwellwert2){
      tone(pin_audio, noten[oktave * 12 + 2]);
      gedrueckt = true;
    }
    
     if(triggernote[2].sensorwert >= schwellwert1){
      tone(pin_audio, noten[oktave * 12 + 4]);
      gedrueckt = true;
    }

    if(triggernote[3].sensorwert >= schwellwert3){
      tone(pin_audio, noten[oktave * 12 + 5]);
      gedrueckt = true;
    }

    if(triggernote[4].sensorwert >= schwellwert2){
      tone(pin_audio, noten[oktave * 12 + 7]);
      gedrueckt = true;
    }
    
    if(triggernote[5].sensorwert >= schwellwert3){
      tone(pin_audio, noten[oktave * 12 + 9]);
      gedrueckt = true;
    }
    if(triggernote[6].sensorwert >= schwellwert2){
      tone(pin_audio, noten[oktave * 12 + 11]);
      gedrueckt = true;
    }
    
    if(triggernote[7].sensorwert >= schwellwert3){
      tone(pin_audio, noten[oktave * 12 + 12]);
      gedrueckt = true;
    }

    if(!gedrueckt){ //stop wenn nichts gedrückt
      noTone(pin_audio);
      digitalWrite(pin_led, LOW);
    }else{
      digitalWrite(pin_led, HIGH);
    }

    bool sw2_gedrueckt = !digitalRead(pin_sw2); //lese pins für Taster ein
    bool sw3_gedrueckt = !digitalRead(pin_sw3);
    if(sw2_gedrueckt){  //wenn
      oktave--;
      delay(150); //warte 150 millisekunden, bis Taster wieder eingelesen werden kann
    }else if(sw3_gedrueckt){
      oktave++;
      delay(150); //warte 150 millisekunden, bis Taster wieder eingelesen werden kann
    }
    if(oktave < 0){ //wenn oktave kleiner als 0 ist, setze Oktave auf 0
      oktave = 0;
    }
    if(oktave > 3){ //wenn oktave größer 3 ist, setze Oktave auf 3
      oktave = 3;
    }
    
  }
}







