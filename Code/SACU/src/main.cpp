#include <Arduino.h>

const int HIP1_BUTTON_PIN = 3;       // the number of the pushbutton pin
const int HIP2_BUTTON_PIN = 4;
const int HIP3_BUTTON_PIN = 5;
const int HIP4_BUTTON_PIN = 6;
const int KNEE1_BUTTON_PIN = 7;
const int KNEE2_BUTTON_PIN = 8;
const int FOOT1_BUTTON_PIN = 9;
const int FOOT2_BUTTON_PIN = 10;
const int SWITCH_PIN = 2;

const int LED_PIN = 13;


// put function declarations here:
int myFunction(int, int);


void setup() {
  Serial.begin(9600);

  // pinMode declaration
  pinMode(HIP1_BUTTON_PIN, INPUT_PULLUP);
  pinMode(HIP2_BUTTON_PIN, INPUT_PULLUP);
  pinMode(HIP3_BUTTON_PIN, INPUT_PULLUP);
  pinMode(HIP4_BUTTON_PIN, INPUT_PULLUP);
  pinMode(KNEE1_BUTTON_PIN, INPUT_PULLUP);
  pinMode(KNEE2_BUTTON_PIN, INPUT_PULLUP);
  pinMode(FOOT1_BUTTON_PIN, INPUT_PULLUP);
  pinMode(FOOT2_BUTTON_PIN, INPUT_PULLUP);

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  pinMode(LED_PIN, OUTPUT);
}

String motor[] = {"HIP1", "HIP2", "HIP3", "HIP4", "KNEE1", "KNEE2", "FOOT1", "FOOT2"};

int currentState_HIP1_Button = 1;        // 0 für gedrückt und 1 für nicht gedrückt ?
int currentState_HIP2_Button = 1;
int currentState_HIP3_Button = 1;
int currentState_HIP4_Button = 1;
int currentState_KNEE1_Button = 1;
int currentState_KNEE2_Button = 1;
int currentState_FOOT1_Button = 1;
int currentState_FOOT2_Button = 1;

int currentState_Switch = 1;

int ledState = LOW;  // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change:
const long interval = 200;  // interval at which to blink (milliseconds)

String active_motor = "NONE";

void loop() {

  // get current state of buttons
  currentState_HIP1_Button = digitalRead(HIP1_BUTTON_PIN);
  currentState_HIP2_Button = digitalRead(HIP2_BUTTON_PIN);
  currentState_HIP3_Button = digitalRead(HIP3_BUTTON_PIN);
  currentState_HIP4_Button = digitalRead(HIP4_BUTTON_PIN);
  currentState_KNEE1_Button = digitalRead(KNEE1_BUTTON_PIN);
  currentState_KNEE2_Button = digitalRead(KNEE2_BUTTON_PIN);
  currentState_FOOT1_Button = digitalRead(FOOT1_BUTTON_PIN);
  currentState_FOOT2_Button = digitalRead(FOOT2_BUTTON_PIN);

  // get current state of switch
  currentState_Switch = digitalRead(SWITCH_PIN);

  // get current state of led
  ledState = digitalRead(LED_PIN);

  if(currentState_Switch == 0){         // 0 = angeschaltet
    // LED on when Switch on and motor_active == 0
    if(active_motor == "NONE"){
      digitalWrite(LED_PIN, HIGH);
      //Serial.println("LED on");
    }
    
    // blink led when mode_active == 1
    else{
      if (millis() - previousMillis >= interval) {
        // save the last time you blinked the LED
        previousMillis = millis();

        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }

        // set the LED with the ledState of the variable:
        digitalWrite(LED_PIN, ledState);
      }
    }


    // HIP 1 motor
    if(currentState_HIP1_Button == 0 and (active_motor== motor[0] or active_motor == "NONE")){       // 0 = gedrückt und mode nicht aktiv
      // actuate
      Serial.println("hip 1 motor on");
      active_motor = motor[0];
    }

    // HIP 2 motor
    else if(currentState_HIP2_Button == 0 and (active_motor == motor[1] or active_motor == "NONE")){       // 0 = gedrückt und mode nicht aktiv
      // actuate
      Serial.println("hip 2 motor on");
      active_motor = motor[1];
    }

    // HIP 3 motor
    else if(currentState_HIP3_Button == 0 and (active_motor == motor[2] or active_motor == "NONE")){       // 0 = gedrückt und mode nicht aktiv
      // actuate
      Serial.println("hip 3 motor on");
      active_motor = motor[2];
    }

    // HIP 4 motor
    else if(currentState_HIP4_Button == 0 and (active_motor == motor[3] or active_motor == "NONE")){       // 0 = gedrückt und mode nicht aktiv
      // actuate
      Serial.println("hip 4 motor on");
      active_motor = motor[3];
    }

    // KNEE 1 motor
    else if(currentState_KNEE1_Button == 0 and (active_motor == motor[4] or active_motor == "NONE")){       // 0 = gedrückt und mode nicht aktiv
      // actuate
      Serial.println("knee 1 motor on");
      active_motor = motor[4];
    }

    // KNEE 2 motor
    else if(currentState_KNEE2_Button == 0 and (active_motor == motor[5] or active_motor == "NONE")){       // 0 = gedrückt und mode nicht aktiv
      // actuate
      Serial.println("knee 2 motor on");
      active_motor = motor[5];
    }

    // FOOT 1 motor
    else if(currentState_FOOT1_Button == 0 and (active_motor == motor[6] or active_motor == "NONE")){       // 0 = gedrückt und mode nicht aktiv
      // actuate
      Serial.println("foot 1 motor on");
      active_motor = motor[6];
    }

    // FOOT 2 motor
    else if(currentState_FOOT2_Button == 0 and (active_motor == motor[7] or active_motor == "NONE")){       // 0 = gedrückt und mode nicht aktiv
      // actuate
      Serial.println("foot 2 motor on");
      active_motor = motor[7];
    }

    // NO MOTOR On
    else{
      Serial.println("motors off");
      active_motor = "NONE";
    }
  }

  else{
    // LED off
    digitalWrite(LED_PIN, LOW);
    //Serial.println("LED off");
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}