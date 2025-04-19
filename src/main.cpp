// note todo lines in this file
#include <Arduino.h>
#include <ezButton.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

void NoteLoop();

// Teensy GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav2;     //xy=361,554
AudioPlaySdWav           playSdWav1;     //xy=363,348
AudioMixer4              mixer1;         //xy=622,446
AudioOutputI2S           i2s1;           //xy=863,440
AudioConnection          patchCord1(playSdWav2, 0, mixer1, 2);
AudioConnection          patchCord2(playSdWav2, 1, mixer1, 3);
AudioConnection          patchCord3(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord4(playSdWav1, 1, mixer1, 1);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=613,589
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7   // Teensy 4 ignores this, uses pin 11
#define SDCARD_SCK_PIN   14  // Teensy 4 ignores this, uses pin 13

// Use these with the Teensy 3.5 & 3.6 & 4.1 SD card
//#define SDCARD_CS_PIN    BUILTIN_SDCARD
//#define SDCARD_MOSI_PIN  11  // not actually used
//#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13

 void setupDebounceTimes();    // declare functions
 void NoteLoop();
 // PK comment I found the ezButton debounce library and it suits the project well. Code below from the EZButton sample here:
 // https://arduinogetstarted.com/tutorials/arduino-button-debounce
 // add in as many buttons as there are notes on the drum
 // map the ezButton definitions to the correct pin numbers on the Teensy 3.6 board
 // For recording a sequence of notes (e.g. a tune melody), write the note ids to a text file on the SD card
 // for playback of a stored tune/ melody load the text file and map the note ids to the sound samples to be played

 // PK todo change the pin numbers below to those conneted to the note pads on the drum
 // todo create ezButton objects that attach to pins
// outer drum notes
 ezButton noteA(16);   
 ezButton noteB(39);   
 ezButton noteC(21);   
 ezButton noteD(20);   //was 17
 ezButton noteE(34);   
 ezButton noteF(35);   
 ezButton noteG(17);   //was 20
 ezButton noteCSharp(38);   // C sharp
 ezButton noteGSharp(37);   
 ezButton noteBFlat(36);   
// Inner notes
ezButton noteGDash(26);   
ezButton noteADash(28);   
ezButton noteBDash(32);   
ezButton noteFSharpDash(31);   
ezButton noteEFlatDash(25);   
ezButton noteBFlatDash(27);    
ezButton noteCDash(29);   
 
 void setup() 
 {
   Serial.begin(9600);
   AudioMemory(8);
   sgtl5000_1.enable();
   sgtl5000_1.volume(0.5);
   SPI.setMOSI(SDCARD_MOSI_PIN);
   SPI.setSCK(SDCARD_SCK_PIN);
   if (!(SD.begin(SDCARD_CS_PIN))) {
     while (1) {
       Serial.println("Unable to access the SD card");
       delay(500);
     }
   }
   mixer1.gain(0, 0.5);
   mixer1.gain(1, 0.5);
   
   delay(1000);
   Serial.println("Connected ok");

   setupDebounceTimes();   // PK - todo ensure the routine has lines for all pads. The debounce time may be adjusted to suit debounce characteristic of drumstick & pad

 }

 
 void loop() 
 {

 NoteLoop(); // MUST call the loop() function first

   if(noteA.isPressed())
   //PK todo add code to play the note use the Teensy example from Arduino IDE trial
     Serial.println("Note A is pressed");
 
//   if(noteA.isReleased())
//     Serial.println("The button 1 is released");
 
   if(noteB.isPressed())
     Serial.println("Note B is pressed");
 
   if(noteC.isPressed())
   Serial.println("Note C is pressed");
 
   if(noteD.isPressed())
   Serial.println("Note D is pressed");
 
   if(noteE.isPressed())
   Serial.println("Note E is pressed");
 
   if(noteF.isPressed())
     Serial.println("Note F is pressed");
 
   if(noteG.isPressed())                 // good to here
   Serial.println("Note G is pressed");
  
   if(noteCSharp.isPressed())
   Serial.println("Note C Sharp is pressed");
 
   if(noteGSharp.isPressed())
   Serial.println("Note G Sharp is pressed");
 
   if(noteBFlat.isPressed())
     Serial.println("Note B Flat is pressed");
 
// inner notes below

   if(noteGDash.isPressed())
   Serial.println("Inner G is pressed");
 
   if(noteADash.isPressed())
   Serial.println("Inner A is pressed");
 
   if(noteBDash.isPressed())
   Serial.println("Inner B is pressed");

   if(noteFSharpDash.isPressed())
   Serial.println("Inner F Sharp is pressed");

   if(noteEFlatDash.isPressed())
   Serial.println("Inner E Flat is pressed");

   if(noteBFlatDash.isPressed())
   Serial.println("Inner B Flat is pressed");

   if(noteCDash.isPressed())
   Serial.println("Inner C is pressed");

 
  }  // end void loop
 

void setupDebounceTimes()
{
  noteA.setDebounceTime(50); // set debounce time to 50 milliseconds
  noteB.setDebounceTime(50); 
  noteC.setDebounceTime(50); 
  noteD.setDebounceTime(50); 
  noteE.setDebounceTime(50); 
  noteF.setDebounceTime(50); 
  noteG.setDebounceTime(50); 
  noteCSharp.setDebounceTime(50); 
  noteGSharp.setDebounceTime(50); 
  noteBFlat.setDebounceTime(50); 
  
  //inner notes
  noteGDash.setDebounceTime(50); 
  noteADash.setDebounceTime(50); 
  noteBDash.setDebounceTime(50); 
  noteFSharpDash.setDebounceTime(50); 
  noteEFlatDash.setDebounceTime(50); 
  noteBFlatDash.setDebounceTime(50); 
  noteCDash.setDebounceTime(50); 
  // etc
}
void NoteLoop()
{
  // outer notes in anti clockwise drum order from C
  noteC.loop(); 
  noteG.loop(); 
  noteD.loop(); 
  noteA.loop(); 
  noteE.loop(); 
  noteB.loop(); 
  noteCSharp.loop(); 
  noteGSharp.loop(); 
  noteBFlat.loop(); 
  noteF.loop(); 

  // inner notes
  noteGDash.loop(); 
  noteADash.loop(); 
  noteBDash.loop(); 
  noteFSharpDash.loop(); 
  noteEFlatDash.loop(); 
  noteBFlatDash.loop(); 
  noteCDash.loop(); 
}