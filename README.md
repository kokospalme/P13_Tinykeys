# TinyKeys
Unterlagen zum Projekt "Luftmesser" (v1.0), C. Wüpping, 2022
##### Das gesamte Projekt inkl. Code unterliegt der Creative Common Lizenz CC BY-NC 4.0 (https://creativecommons.org/licenses/by-nc/4.0/deed.de)
<img src="https://github.com/kokospalme/P13_Tinykeys/blob/main/Bilder/photo_5273793573030053222_y.jpg">

## getting started (hardware v1.0)
Was du benötigst
- Tinykeys Platine
- [Tinykeys Gehäuse](https://github.com/kokospalme/P13_Tinykeys/tree/main/Case)
- Bauteile:
  - Widerstände 1MΩ: R1,R2,R3,R4,R5,R6,R7,R8
  - Widerstand 2kΩ: R10
  - Widerstand 47kΩ: R11
  - Widerstand 4,7k: R12
  - LED 3mm: D1
  - Taster: SW1, SW2
  - ISP-Stecker 6 pin: J2
  - Adio-Buchse 3.5mm Klinke: J3
  - Potentiometer 10kΩ: RV1d
  - Stiftleiste 2x2.54: JP1
  - Jumper 2.54
- 8 dünne Drähte (ca 0.3mm^2)
  - 40mm (C)
  - 60mm (D)
  - 80mm (E)
  - 100mm (F)
  - 120mm (G)
  - 140mm (A)
  - 160mm (H)
  - 180mm (C2)
- Alufolie (alternativ Kupfer, ist aber teuer)
- 2 Schrauben 3 x 4mm (Durchmesser X Länge)
- Computer/Laptop
- [Arduino IDE](https://www.arduino.cc/en/software) oder andere Programmierumgebung, zB [SLOEBER](http://eclipse.baeyens.it/) oder [PlatformIO](https://platformio.org/)
- [Programmcode ("sketch")](https://github.com/kokospalme/P13_Tinykeys/tree/main/Code)
- ISP Programmer + Kabel

###### <img src="https://hobby-elektronik.ch/images/product_images/popup_images/USBasp-ISP-Programmer-fuer-Atmel:__:854_0.jpg">

- Lötstation
- Lötzinn (je dünner, desto besser)
- Zangen (Spitzzange, Kombizange oder ähnliches)
- Schraubendreher (Kreuzschlitz)

## Schaltplan (SCH)
https://github.com/kokospalme/P13_Tinykeys/blob/main/Schaltplan/TinyKeys_SCH_v1.1.pdf

## Lötreihenfolge
Damit du bequem an alle Bauteile herankommst, hältst du am besten eine bestimmte Reihenfolge beim Löten der Bauteile ein.
Du fängst ganz einfach mit den kleinsten/niedrigsten Bauteilen an, bis du beim höchsten angekommen bist.
Eine optimale Reihenfolge ergibt sich wie folgt:
- Widerstände 1MΩ: R1,R2,R3,R4,R5,R6,R7,R8
- LED 3mm: D1
- Taster: SW1, SW2
- Widerstand 2kΩ: R10
- Adio-Buchse 3.5mm Klinke: J3
- Widerstand 47kΩ: R11
- Widerstand 4,7k: R12
- ISP-Stecker 6 pin: J2
- Stiftleiste 2x2.54: JP1
- Potentiometer 10kΩ: RV1
### Bauteile (BOM)
https://github.com/kokospalme/P13_Tinykeys/tree/main/BOM

## Arduino Code v1.0


