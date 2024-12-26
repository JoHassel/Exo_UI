#include <Arduino.h>

#include <Adafruit_GFX.h>       // include Adafruit graphics library
#include <Adafruit_ILI9341.h>   // include Adafruit ILI9341 TFT library

#include "graphiclayout.h"
#include "bitmaps.h"
#include "acoustic.h"
#include "vibration.h"

#define TFT_CS    10            // TFT CS  pin is connected to pin 10
#define TFT_RST   15            // TFT RST pin is connected to pin 15
#define TFT_DC    9             // TFT DC  pin is connected to pin 9

const int TOGGLE_BUTTON_PIN = 5;    // toggle button is connected to pin 5
const int SELECT_BUTTON_PIN = 8;    // select button is connected to pin 8

const int PIEZO_PIN = 6;            // piezo is connected to pin 6
const int VIBRATION_PIN = 7;        // vibrator is connected to pin 7

// initialize ILI9341 TFT library
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(9600);

  tft.begin();
  tft.fillScreen(ILI9341_BLACK);

  // pinMode declaration
  pinMode(TOGGLE_BUTTON_PIN, INPUT_PULLUP);     // Button: switch/toggle through mode
  pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP);     // Button: select mode

  pinMode(PIEZO_PIN, OUTPUT);                   // Piezo for sound, when toggling through mode
  pinMode(VIBRATION_PIN, OUTPUT);               // Vibrator for vibration, when selecting mode
  
  // display Rise logo
  // multi colored
  int h = 310,w = 240, row, col, buffidx=0;
  for (row=0; row<h; row++) { // For each scanline...
    for (col=0; col<w; col++) { // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      tft.drawPixel(col, row, pgm_read_word(riselogo240x310 + buffidx));
      buffidx++;
    } // end pixel
  }

  delay(3000);
  tft.fillScreen(ILI9341_BLACK);        // shift to black screen
}

// define states of buttons
int currentState_toggleButton = 1;        // 0 -> pushed, 1 -> not pushed
int currentState_selectButton = 1;

// define old states of button
int currentState_toggleButton_old = 1;
int currentState_selectButton_old = 1;

// set time period for sound
uint32_t period_sound = 200;
uint32_t tStart_sound = 0;

// current toggled modes
int toggled_mode = 0;         // see mode[]         // 0 -> Walk, 1 -> Step, 2 -> Stairs, 3 -> Sit down, 4 -> Stand up
int toggled_step_mode = 0;    // see mode_step[]    // 0 -> forward, 1 -> right, 2 -> backward, 3 -> left, 4 -> back
int toggled_stairs_mode = 0;  // see mode_stairs[]  // 0 -> upstairs, 1 -> downstairs, 3 -> back

// current state of exo
int mode_selected = 0;        // 0 -> mode inactive , 1 -> mode active, 2 -> step menu, 3 -> stairs menu

// variables to acces the following arrays and initialize starting mode and status
int nr_mode = 9;          // none
int nr_status = 10;       // Seated
int nr_last_mode = 9;     // none

// MODE complete array
String expandedMode[] = {"Walk", "Forward Step", "Right Step", "Backward Step", "Left Step", "Stairs up", "Stairs down", "Sit down", "Stand Up", "none"};

// MODE array for menus: main, step and stairs
String mode[] = {"Walk", "Step", "Stairs", "Sit down", "Stand Up"};   // man braucht stand up nicht?
String mode_step[] = {"Forward", "Right", "Backward", "Left", "Back"};
String mode_stairs[] = {"Upstairs", "Downstairs", "Back"};

// STATUS array
String status[] = {"Walking", "Forward Stepping", "Right Stepping", "Backward Stepping", "Left Stepping", "Walking upstairs", "Walking downstairs", "Sitting down", "Standing Up", "Standing", "Seated"};

// signal to main controller
String signal_2_mc = "";

void loop() {

  // get the last states of buttons
  currentState_toggleButton_old = currentState_toggleButton;
  currentState_selectButton_old = currentState_selectButton;

  // read states of buttons
  currentState_toggleButton = digitalRead(TOGGLE_BUTTON_PIN);
  currentState_selectButton = digitalRead(SELECT_BUTTON_PIN);

  // check if sound can be turned off
  if((millis()-tStart_sound) > period_sound){
    turnOffSound(PIEZO_PIN);
  }

  // turn off vibration
  turnOffVibration(VIBRATION_PIN);


  // ACTIVE MODES /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if(mode_selected == 1){

    // if select button is pushed
    if(currentState_selectButton != currentState_selectButton_old && currentState_selectButton == 0){

        // set to mode inactive
        mode_selected = 0;

        // update status
        if(expandedMode[nr_last_mode] == "Sit down"){
          nr_status = 10;
        }
        else{
          nr_status = 9;
        }

        // turn on sound
        turnOnSoundSelectMode(PIEZO_PIN);
        tStart_sound = millis();

        // fill screen with black for next layout
        tft.fillScreen(ILI9341_BLACK);
      }

    // if mode inactive -> StandingLayout or SittingLayout (toggled mode is green)
    if(mode_selected == 0){
      
      // if status is STANDING
      if(nr_status != 10){
        makeStandingLayout(tft, mode[toggled_mode], status[nr_status], expandedMode[nr_last_mode]);
        signal_2_mc = "mode inactive";
        Serial.println(signal_2_mc);
      }

      // if status is SEATED
      else{
        makeSeatedLayout(tft, expandedMode[nr_last_mode]);
        signal_2_mc = "mode inactive";
        Serial.println(signal_2_mc);
      }
    }

    // if mode active -> InModeLayout
    else{
      makeInModeLayout(tft, expandedMode[nr_mode], status[nr_status], expandedMode[nr_last_mode]);
      signal_2_mc = "mode active: " + expandedMode[nr_mode];
      Serial.println(signal_2_mc);
    }
  }

  // PASSIVE MODES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  else{

    // Seated /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(status[nr_status] == "Seated"){    // if nr_status = 10

      // if select button is pushed
      if(currentState_selectButton != currentState_selectButton_old && currentState_selectButton == 0){

        // set to mode active
        mode_selected = 1;
        
        // update status and mode
        nr_status = 8;            // Standing up
        nr_mode = 8;              // Stand up
        nr_last_mode = nr_mode;   // Stand up

        // turn sound on
        turnOnSoundSelectMode(PIEZO_PIN);
        tStart_sound = millis();

        // fill screen with black for next layout
        tft.fillScreen(ILI9341_BLACK);
      }

      // if mode is inactive -> SeatedLayout
      if(mode_selected == 0){
        makeSeatedLayout(tft, expandedMode[nr_last_mode]);
        signal_2_mc = "mode inactive";
        Serial.println(signal_2_mc);
      }

      // if mode is active -> InModeLayout
      else{
        makeInModeLayout(tft, expandedMode[nr_mode], status[nr_status], expandedMode[nr_last_mode]);
        signal_2_mc = "mode active: " + expandedMode[8];
        Serial.println(signal_2_mc);
      }
    }

    // Standing ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    else if(status[nr_status] == "Standing"){   // if nr_status = 9
    
      // if toggle button pushed
      if(currentState_toggleButton != currentState_toggleButton_old && currentState_toggleButton == 0){

        // if mode inactive -> toggle through main menu
        if(mode_selected == 0){
          toggled_mode+=1;

          if(toggled_mode > 3){
            toggled_mode = 0;
          }
        }

        // if step selected -> toggle through step menu
        else if(mode_selected == 2){
          toggled_step_mode+=1;

          if(toggled_step_mode > 4){
            toggled_step_mode = 0;
          }
        }

        // if stairs selected -> toggle through stairs menu
        else if(mode_selected == 3){
          toggled_stairs_mode+=1;

          if(toggled_stairs_mode > 2){
            toggled_stairs_mode = 0;
          }
        }

        // turn on vibration while toggling
        turnOnVibration(VIBRATION_PIN);
      }

      // if select button pushed
      if(currentState_selectButton != currentState_selectButton_old && currentState_selectButton == 0){

        // check if step or stairs is selected
        if(mode_selected == 2 or mode_selected == 3){

          // active step menu
          if(mode_selected == 2){

            // if not back is toggled
            if(toggled_step_mode < 4){
              // update mode, status and last_mode
              nr_mode = toggled_step_mode + 1;
              nr_status = nr_mode;
              nr_last_mode = nr_mode;

              // set to mode active
              mode_selected = 1;

              // turn on sound when mode selected
              turnOnSoundSelectMode(PIEZO_PIN);
              tStart_sound = millis();
            }

            // if back is toggled
            else{

              // set to mode inactive (switch to main menu)
              mode_selected = 0;

              // turn on sound when back to main menu
              turnOnSoundToggleMode(PIEZO_PIN);
              tStart_sound = millis();
            }
          }

          // active stairs menu
          else if(mode_selected == 3){

            // if not back is toggled
            if(toggled_stairs_mode < 2){

              // update mode, status and last_mode
              nr_mode = toggled_stairs_mode + 5;
              nr_status = nr_mode;
              nr_last_mode = nr_mode;

              // set to mode active
              mode_selected = 1;

              // turn on sound when mode selected
              turnOnSoundSelectMode(PIEZO_PIN);
              tStart_sound = millis();
            }

            // if back is toggled
            else{
              
              // set to mode inactive (switch to main menu)
              mode_selected = 0;

              // turn on sound when back to main menu
              turnOnSoundToggleMode(PIEZO_PIN);
              tStart_sound = millis();
            }
          }
        }

        // if mode was inactive
        else{

          // when mode WALK is toggled
          if(toggled_mode == 0){

            // set mode to active
            mode_selected = 1;
            
            // update status, mode and last_mode
            nr_status = 0;              // Status: Walking
            nr_mode = 0;                // Mode: Walk
            nr_last_mode = nr_mode;     // Last Mode: Walk

            // turn sound on
            turnOnSoundSelectMode(PIEZO_PIN);
            tStart_sound = millis();
          }

          // when mode SIT DOWN is toggled
          else if(toggled_mode == 3){

            // set mode to active
            mode_selected = 1;

            // update status, mode and last_mode
            nr_status = 7;              // Status: Sitting down
            nr_mode = 7;                // Mode: Sit down
            nr_last_mode = nr_mode;     // Last Mode: Sit down

            // turn sound on
            turnOnSoundSelectMode(PIEZO_PIN);
            tStart_sound = millis();
          }

          // when mode STEP is toggled -> jump to step menu
          else if(toggled_mode == 1){

            // set mode to step menu
            mode_selected = 2;

            // turn on sound when switching to submenu
            turnOnSoundToggleMode(PIEZO_PIN);
            tStart_sound = millis();
          }

          // when mode STAIRS is toggled -> jump to stairs menu
          else{

            // set mode to stairs menu
            mode_selected = 3;

            // turn on sound when switching to submenu
            turnOnSoundToggleMode(PIEZO_PIN);
            tStart_sound = millis();
          }
        }

        // fill screen with black for next layout
        tft.fillScreen(ILI9341_BLACK);
      }

      // if mode inactive -> StandingLayout (toggled mode is green)
      if(mode_selected == 0){
        makeStandingLayout(tft, mode[toggled_mode], status[nr_status], expandedMode[nr_last_mode]);
        signal_2_mc = "mode inactive";
        Serial.println(signal_2_mc);
      }

      // if mode is step menu -> StepLayout (toggled mode is green)
      else if(mode_selected == 2){
        makeStepLayout(tft, mode_step[toggled_step_mode], status[nr_status], expandedMode[nr_last_mode]);
        signal_2_mc = "mode inactive";
        Serial.println(signal_2_mc);
      }

      // if mode is stairs menu -> StairsLayout (toggled mode is green)
      else if(mode_selected == 3){
        // make Stairs Layout
        makeStairsLayout(tft, mode_stairs[toggled_stairs_mode], status[nr_status], expandedMode[nr_last_mode]);
        signal_2_mc = "mode inactive";
        Serial.println(signal_2_mc);
      }

      // if mode active -> InModeLayout
      else{
        makeInModeLayout(tft, expandedMode[nr_mode], status[nr_status], expandedMode[nr_last_mode]);
        signal_2_mc = "mode active: " + expandedMode[nr_mode];
        Serial.println(signal_2_mc);
      }
    }
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}