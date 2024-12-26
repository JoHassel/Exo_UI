#ifndef GRAPHICLAYOUT_H
#define GRAPHICLAYOUT_H

#include <Arduino.h>

#include <Adafruit_GFX.h>       // include Adafruit graphics library
#include <Adafruit_ILI9341.h>   // include Adafruit ILI9341 TFT library

#include "bitmaps.h"

// https://gist.github.com/Kongduino/36d152c81bbb1214a2128a2712ecdd18 for colors
// https://stackoverflow.com/questions/13720937/c-defined-16bit-high-color for colors

// Color definitions
#define ILI9341_RISEORANGE 0xfb60       // rgb: 255, 108, 0 | Hex: #FF6C00
#define ILI9341_BLACK 0x0000       ///<   0,   0,   0
#define ILI9341_NAVY 0x000F        ///<   0,   0, 123
#define ILI9341_DARKGREEN 0x03E0   ///<   0, 125,   0
#define ILI9341_DARKCYAN 0x03EF    ///<   0, 125, 123
#define ILI9341_MAROON 0x7800      ///< 123,   0,   0
#define ILI9341_PURPLE 0x780F      ///< 123,   0, 123
#define ILI9341_OLIVE 0x7BE0       ///< 123, 125,   0
#define ILI9341_LIGHTGREY 0xC618   ///< 198, 195, 198
#define ILI9341_DARKGREY 0x7BEF    ///< 123, 125, 123
#define ILI9341_BLUE 0x001F        ///<   0,   0, 255
#define ILI9341_GREEN 0x07E0       ///<   0, 255,   0
#define ILI9341_CYAN 0x07FF        ///<   0, 255, 255
#define ILI9341_RED 0xF800         ///< 255,   0,   0
#define ILI9341_MAGENTA 0xF81F     ///< 255,   0, 255
#define ILI9341_YELLOW 0xFFE0      ///< 255, 255,   0
#define ILI9341_WHITE 0xFFFF       ///< 255, 255, 255
#define ILI9341_ORANGE 0xFD20      ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define ILI9341_PINK 0xFC18        ///< 255, 130, 198

// text to display infront of status or last mode
String status_str = "";       // S: <status>
String last_mode_str = "";    // LM: <last mode>

// make Layout for Standing Status
void makeStandingLayout(Adafruit_ILI9341 tft, String selected_mode, String status, String last_mode){
  int n_y_fields = 7;
  int n_x_fields = 2;
  int gap_between_fields = 5;

  // field measures
  int field_height = (tft.height()-((n_y_fields+1)*gap_between_fields))/n_y_fields;
  int field_width = (tft.width()-((n_x_fields+1)*gap_between_fields))/n_x_fields;
  int field_corner_radius = 10;

  // text size
  int text_size = 2;

  // run variables
  int k_x_fields = 0;
  int k_y_fields = 0;
  int n_drawn_fields = 0;


  // Stop or Back /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // array for stop or back
  String stop_back[] = {"Stop", "Back"};

  // field position
  int field_position[] = {gap_between_fields, gap_between_fields};

  // text position
  int text_width = (stop_back[0].length())*3*text_size;
  int text_position[] = {field_position[0] + (2*field_width+gap_between_fields)/2 - text_width, field_position[1] + field_height/2 - 7};

  // draw stop/back field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_DARKGREY);

  // write text
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(stop_back[0]);


  // Modes ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // mode array
  String modes[] = {"Walk", "Step", "Stairs", "Sit down"};

  // color
  const unsigned char selected_color = ILI9341_WHITE;

  // draw mode fields
  int n_mode_fields[] = {2, 2};

  // update field position
  field_position[1] += field_height + gap_between_fields;

  // update text position & color
  tft.setTextColor(ILI9341_WHITE);
  text_width = (modes[n_drawn_fields].length())*3*text_size;
  text_position[0] = field_position[0] + field_width/2 - text_width;
  text_position[1] = field_position[1] + 2*field_height + gap_between_fields - 20;

  // symbol position
  int symbol_position[] = {field_position[0] + field_width/2 - 25, field_position[1] + (2*field_height+gap_between_fields)/2 - 35};


  for(k_y_fields; k_y_fields<n_mode_fields[1]; k_y_fields+=1) {

    for(k_x_fields; k_x_fields<n_mode_fields[0]; k_x_fields+=1) {
      if(selected_mode == modes[n_drawn_fields])
      {
        // draw field
        tft.drawRoundRect(field_position[0], field_position[1], field_width, 2*field_height + gap_between_fields, field_corner_radius, ILI9341_GREEN);

        // add symbol
        tft.drawBitmap(symbol_position[0],symbol_position[1],arrayOfModeSymbols[n_drawn_fields],50,50,ILI9341_GREEN);

        // write text
        tft.setTextColor(ILI9341_GREEN);
        tft.setCursor(text_position[0], text_position[1]);
        tft.setTextSize(text_size);
        tft.println(modes[n_drawn_fields]);
        tft.setTextColor(ILI9341_WHITE);
      }
      else{
        // draw field
        tft.drawRoundRect(field_position[0], field_position[1], field_width, 2*field_height + gap_between_fields, field_corner_radius, ILI9341_WHITE);

        // add symbol
        tft.drawBitmap(symbol_position[0],symbol_position[1],arrayOfModeSymbols[n_drawn_fields],50,50,ILI9341_WHITE);

        // write text
        tft.setCursor(text_position[0], text_position[1]);
        tft.setTextSize(text_size);
        tft.println(modes[n_drawn_fields]);
      }


      n_drawn_fields += 1;

      // update field position
      field_position[0] += field_width + gap_between_fields;

      // update text width
      text_width = (modes[n_drawn_fields].length())*3*text_size;

      // update text position
      text_position[0] = field_position[0] + field_width/2 - text_width;

      // update symbol position
      symbol_position[0] = field_position[0] + field_width/2 - 25;
    }

    // reset k_x_fields
    k_x_fields = 0;

    if(k_y_fields != 1){
      // update field positions
      field_position[0] = gap_between_fields;   // reset to gap_between_fields
      field_position[1] += 2*field_height + 2*gap_between_fields;

      // update text position
      text_position[0] = field_position[0] + field_width/2 - text_width;
      text_position[1] = field_position[1] + 2*field_height + gap_between_fields - 20;

      // update symbol position
      symbol_position[0] = field_position[0] + field_width/2 - 25;
      symbol_position[1] = field_position[1] + (2*field_height+gap_between_fields)/2 - 35;
    }
  }


  // Status ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // update field positions
  field_position[0] = gap_between_fields;   // reset to gap_between_fields
  field_position[1] += 2*field_height + 2*gap_between_fields;

  // update text position
  text_width = ((status_str + status).length())*3*text_size;
  text_position[0] = field_position[0] + (2*field_width+gap_between_fields)/2 - text_width;
  text_position[1] = field_position[1] + field_height/2 - 7;

  // draw status field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_RISEORANGE);

  // write text
  tft.setTextColor(ILI9341_RISEORANGE);
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(status_str + status);


  // Last Mode ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // update field position
  field_position[1] += field_height + gap_between_fields;

  // update text position
  text_width = ((last_mode_str + last_mode).length())*3*text_size;
  text_position[0] = field_position[0] + (2*field_width+gap_between_fields)/2 - text_width;
  text_position[1] = field_position[1] + field_height/2 - 7;

  // draw last mode field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_RISEORANGE);

  // write text
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(last_mode_str + last_mode);

}

// make Layout for Seated Status
void makeSeatedLayout(Adafruit_ILI9341 tft, String last_mode){
  int n_y_fields = 7;
  int n_x_fields = 2;
  int gap_between_fields = 5;

  // field measures
  int field_height = (tft.height()-((n_y_fields+1)*gap_between_fields))/n_y_fields;
  int field_width = (tft.width()-((n_x_fields+1)*gap_between_fields))/n_x_fields;
  int field_corner_radius = 10;

  // text size
  int text_size = 2;

  // run variables
  int k_x_fields = 0;
  int k_y_fields = 0;


  // Stop or Back /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // array for stop or back
  String stop_back[] = {"Stop", "Back"};

  // field position
  int field_position[] = {gap_between_fields, gap_between_fields};

  // text position
  int text_width = (stop_back[0].length())*3*text_size;
  int text_position[] = {field_position[0] + (2*field_width+gap_between_fields)/2 - text_width, field_position[1] + field_height/2 - 7};

  // draw stop/back field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_DARKGREY);

  // write text
  tft.setTextColor(ILI9341_DARKGREY);
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(stop_back[0]);


  // Modes ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // mode array
  String mode = "Stand up";

  // update field position
  field_position[1] += field_height + gap_between_fields;

  // update text position & color
  tft.setTextColor(ILI9341_GREEN);
  text_width = (mode.length())*3*text_size;
  text_position[0] = field_position[0] + (2*field_width+gap_between_fields)/2 - text_width;
  text_position[1] = field_position[1] + (4*field_height + 3*gap_between_fields) - 20;

  // symbol position
  int symbol_position[] = {field_position[0] + (2*field_width+gap_between_fields)/2 - 25, field_position[1] + (4*field_height+3*gap_between_fields)/2 - 35};


  // draw field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width + gap_between_fields, 4*field_height + 3*gap_between_fields, field_corner_radius, ILI9341_GREEN);

  // add symbol
  tft.drawBitmap(symbol_position[0],symbol_position[1],arrayOfModeSymbols[4],50,50,ILI9341_GREEN);

  // write text
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(mode);
  

  // Status ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // Array for status
  String status = "Seated";

  // update field positions
  field_position[1] += 4*field_height + 4*gap_between_fields;

  // update text position
  text_width = ((status_str + status).length())*3*text_size;
  text_position[0] = field_position[0] + (2*field_width+gap_between_fields)/2 - text_width;
  text_position[1] = field_position[1] + field_height/2 - 7;

  // draw status field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_RISEORANGE);

  // write text
  tft.setTextColor(ILI9341_RISEORANGE);
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(status_str + status);


  // Last Mode ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // update field position
  field_position[1] += field_height + gap_between_fields;

  // update text position
  text_width = ((last_mode_str + last_mode).length())*3*text_size;
  text_position[0] = field_position[0] + (2*field_width+gap_between_fields)/2 - text_width;
  text_position[1] = field_position[1] + field_height/2 - 7;

  // draw last mode field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_RISEORANGE);

  // write text
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(last_mode_str + last_mode);

}

// make Layout while in active Status
void makeInModeLayout(Adafruit_ILI9341 tft, String selected_mode, String status, String last_mode){
  int n_y_fields = 7;
  int n_x_fields = 2;
  int gap_between_fields = 5;

  // field measures
  int field_height = (tft.height()-((n_y_fields+1)*gap_between_fields))/n_y_fields;
  int field_width = (tft.width()-((n_x_fields+1)*gap_between_fields))/n_x_fields;
  int field_corner_radius = 10;

  // text size
  int text_size = 2;

  // run variables
  int k_x_fields = 0;
  int k_y_fields = 0;
  int n_drawn_fields = 0;


  // Stop or Back /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // array for stop or back
  String stop_back[] = {"Stop", "Back"};

  // field position
  int field_position[] = {gap_between_fields, gap_between_fields};

  // text position
  int text_width = (stop_back[0].length())*3*text_size;
  int text_position[] = {field_position[0] + (2*field_width+gap_between_fields)/2 - text_width, field_position[1] + field_height/2 - 7};

  // draw stop/back field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_RED);

  // write text
  tft.setTextColor(ILI9341_RED);
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(stop_back[0]);


  // Modes ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // mode array
  String modes[] = {"Walk", "Step", "Stairs", "Sit down"};

  // draw mode fields
  int n_mode_fields[] = {2, 2};

  // update field position
  field_position[1] += field_height + gap_between_fields;

  // update text position & color
  tft.setTextColor(ILI9341_DARKGREY);
  text_width = (modes[n_drawn_fields].length())*3*text_size;
  text_position[0] = field_position[0] + field_width/2 - text_width;
  text_position[1] = field_position[1] + 2*field_height + gap_between_fields - 20;

  // symbol position
  int symbol_position[] = {field_position[0] + field_width/2 - 25, field_position[1] + (2*field_height+gap_between_fields)/2 - 35};


  for(k_y_fields; k_y_fields<n_mode_fields[1]; k_y_fields+=1) {

    for(k_x_fields; k_x_fields<n_mode_fields[0]; k_x_fields+=1) {
      // draw field
      tft.drawRoundRect(field_position[0], field_position[1], field_width, 2*field_height + gap_between_fields, field_corner_radius, ILI9341_DARKGREY);

      // add symbol
      tft.drawBitmap(symbol_position[0],symbol_position[1],arrayOfModeSymbols[n_drawn_fields],50,50,ILI9341_DARKGREY);

      // write text
      tft.setCursor(text_position[0], text_position[1]);
      tft.setTextSize(text_size);
      tft.println(modes[n_drawn_fields]);


      n_drawn_fields += 1;

      // update field position
      field_position[0] += field_width + gap_between_fields;

      // update text width
      text_width = (modes[n_drawn_fields].length())*3*text_size;

      // update text position
      text_position[0] = field_position[0] + field_width/2 - text_width;

      // update symbol position
      symbol_position[0] = field_position[0] + field_width/2 - 25;
    }

    // reset k_x_fields
    k_x_fields = 0;

    if(k_y_fields != 1){
      // update field positions
      field_position[0] = gap_between_fields;   // reset to gap_between_fields
      field_position[1] += 2*field_height + 2*gap_between_fields;

      // update text position
      text_position[0] = field_position[0] + field_width/2 - text_width;
      text_position[1] = field_position[1] + 2*field_height + gap_between_fields - 20;

      // update symbol position
      symbol_position[0] = field_position[0] + field_width/2 - 25;
      symbol_position[1] = field_position[1] + (2*field_height+gap_between_fields)/2 - 35;
    }
  }


  // Status ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // update field positions
  field_position[0] = gap_between_fields;   // reset to gap_between_fields
  field_position[1] += 2*field_height + 2*gap_between_fields;

  // update text position
  text_width = ((status_str + status).length())*3*text_size;
  text_position[0] = field_position[0] + (2*field_width+gap_between_fields)/2 - text_width;
  text_position[1] = field_position[1] + field_height/2 - 7;

  // draw status field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_RISEORANGE);

  // write text
  tft.setTextColor(ILI9341_RISEORANGE);
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(status_str + status);


  // Last Mode ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

// make Layout for Step Menu
void makeStepLayout(Adafruit_ILI9341 tft, String selected_mode, String status, String last_mode){
  int n_y_fields = 7;
  int n_x_fields = 2;
  int gap_between_fields = 5;

  // field measures
  int field_height = (tft.height()-((n_y_fields+1)*gap_between_fields))/n_y_fields;
  int field_width = (tft.width()-((n_x_fields+1)*gap_between_fields))/n_x_fields;
  int field_corner_radius = 10;

  // text size
  int text_size = 2;

  // run variables
  int k_x_fields = 0;
  int k_y_fields = 0;
  int n_drawn_fields = 0;


  // Stop or Back /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // array for stop or back
  String stop_back[] = {"Stop", "Back"};

  // field position
  int field_position[] = {gap_between_fields, gap_between_fields};

  // text position
  int text_width = (stop_back[1].length())*3*text_size;
  int text_position[] = {field_position[0] + (2*field_width+gap_between_fields)/2 - text_width, field_position[1] + field_height/2 - 7};

  if(selected_mode == stop_back[1]){   // if selected_mode = "Back" -> display back-field green
    // draw stop/back field
    tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_GREEN);

    // write text
    tft.setTextColor(ILI9341_GREEN);
    tft.setCursor(text_position[0], text_position[1]);
    tft.setTextSize(text_size);
    tft.println(stop_back[1]);
  }
  else{   // if selected_mode not "Back" -> display back-field white
    // draw stop/back field
    tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_WHITE);

    // write text
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(text_position[0], text_position[1]);
    tft.setTextSize(text_size);
    tft.println(stop_back[1]);
  }


  // Modes ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // amount of field for arrows
  int n_fields_arrows_matrix = 3;

  // field measures for arrows
  int field_height_arrows = (4*field_height+gap_between_fields)/n_fields_arrows_matrix;
  int field_width_arrows = (2*field_width-gap_between_fields)/n_fields_arrows_matrix;
  
  // mode array
  String modes[] = {"Forward", "Right", "Backward", "Left"};
  int n_modes = 4;

  
  // make field, text and symbols
  for(n_drawn_fields; n_drawn_fields < n_modes; n_drawn_fields+=1){
    
    // Forward
    if(n_drawn_fields==0){
      // update field position
      field_position[0] += field_width_arrows+gap_between_fields;
      field_position[1] += field_height+gap_between_fields;
    }

    // Right
    else if(n_drawn_fields==1){
      // update field position
      field_position[0] += field_width_arrows+gap_between_fields;
      field_position[1] += field_height_arrows+gap_between_fields;
    }

    // Backward
    else if(n_drawn_fields==2){
      // update field position
      field_position[0] -= field_width_arrows+gap_between_fields;
      field_position[1] += field_height_arrows+gap_between_fields;
    }

    // Left
    else if(n_drawn_fields==3){
      // update field position
      field_position[0] -= field_width_arrows+gap_between_fields;
      field_position[1] -= field_height_arrows+gap_between_fields;
    }

    // update text position & color
    tft.setTextColor(ILI9341_WHITE);
    text_width = (modes[n_drawn_fields].length())*3*text_size;
    text_position[0] = field_position[0] + field_width_arrows/2 - text_width;
    text_position[1] = field_position[1] + field_height_arrows - 20;

    // symbol position
    int symbol_position[] = {field_position[0] + field_width_arrows/2 - 25, field_position[1] + field_height_arrows/2 - 25};

    // make field green if mode == selected mode, else make white
    if(selected_mode == modes[n_drawn_fields])
    {
      // draw field
      tft.drawRoundRect(field_position[0], field_position[1], field_width_arrows, field_height_arrows, field_corner_radius, ILI9341_GREEN);

      // add symbol
      tft.drawBitmap(symbol_position[0],symbol_position[1],arrayOfModeSymbols[n_drawn_fields+5],50,50,ILI9341_GREEN);
    }
    else{
      // draw field
      tft.drawRoundRect(field_position[0], field_position[1], field_width_arrows, field_height_arrows, field_corner_radius, ILI9341_WHITE);

      // add symbol
      tft.drawBitmap(symbol_position[0],symbol_position[1],arrayOfModeSymbols[n_drawn_fields+5],50,50,ILI9341_WHITE);
    }
  }


  // Status ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // update field positions
  field_position[1] += 2*field_height_arrows + 2*gap_between_fields;

  // update text position
  text_width = ((status_str + status).length())*3*text_size;
  text_position[0] = field_position[0] + (2*field_width+gap_between_fields)/2 - text_width;
  text_position[1] = field_position[1] + field_height/2 - 7;

  // draw status field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_RISEORANGE);

  // write text
  tft.setTextColor(ILI9341_RISEORANGE);
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(status_str + status);


  // Last Mode ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // update field position
  field_position[1] += field_height + gap_between_fields;

  // update text position
  text_width = ((last_mode_str + last_mode).length())*3*text_size;
  text_position[0] = field_position[0] + (2*field_width+gap_between_fields)/2 - text_width;
  text_position[1] = field_position[1] + field_height/2 - 7;

  // draw last mode field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_RISEORANGE);

  // write text
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(last_mode_str + last_mode);

}

// make Layout for Stairs Menu
void makeStairsLayout(Adafruit_ILI9341 tft, String selected_mode, String status, String last_mode){
  int n_y_fields = 7;
  int n_x_fields = 2;
  int gap_between_fields = 5;

  // field measures
  int field_height = (tft.height()-((n_y_fields+1)*gap_between_fields))/n_y_fields;
  int field_width = (tft.width()-((n_x_fields+1)*gap_between_fields))/n_x_fields;
  int field_corner_radius = 10;

  // text size
  int text_size = 2;

  // run variables
  int k_x_fields = 0;
  int k_y_fields = 0;
  int n_drawn_fields = 0;


  // Stop or Back /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // array for stop or back
  String stop_back[] = {"Stop", "Back"};

  // field position
  int field_position[] = {gap_between_fields, gap_between_fields};

  // text position
  int text_width = (stop_back[1].length())*3*text_size;
  int text_position[] = {field_position[0] + (2*field_width+gap_between_fields)/2 - text_width, field_position[1] + field_height/2 - 7};

  if(selected_mode == stop_back[1]){   // if selected_mode = "Back" -> display back-field green
    // draw stop/back field
    tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_GREEN);

    // write text
    tft.setTextColor(ILI9341_GREEN);
    tft.setCursor(text_position[0], text_position[1]);
    tft.setTextSize(text_size);
    tft.println(stop_back[1]);
  }
  else{   // if selected_mode not "Back" -> display back-field white
    // draw stop/back field
    tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_WHITE);

    // write text
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(text_position[0], text_position[1]);
    tft.setTextSize(text_size);
    tft.println(stop_back[1]);
  }


  // Modes ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // amount of field for arrows
  int n_fields_arrows_matrix = 3;

  // field measures for arrows
  int field_height_arrows = (4*field_height+gap_between_fields)/n_fields_arrows_matrix;
  int field_width_arrows = (2*field_width-gap_between_fields)/n_fields_arrows_matrix;
  
  // mode array
  String modes[] = {"Upstairs", "Downstairs"};
  int n_modes = 2;

  
  // make field, text and symbols
  for(n_drawn_fields; n_drawn_fields < n_modes; n_drawn_fields+=1){
    
    // Upstairs
    if(n_drawn_fields==0){
      // update field position
      field_position[0] += field_width_arrows+gap_between_fields;
      field_position[1] += field_height+gap_between_fields;
    }

    // Downstairs
    else if(n_drawn_fields==1){
      // update field position
      field_position[1] += 2*field_height_arrows+2*gap_between_fields;
    }

    // update text position & color
    tft.setTextColor(ILI9341_WHITE);
    text_width = (modes[n_drawn_fields].length())*3*text_size;
    text_position[0] = field_position[0] + field_width_arrows/2 - text_width;
    text_position[1] = field_position[1] + field_height_arrows - 20;

    // symbol position
    int symbol_position[] = {field_position[0] + field_width_arrows/2 - 25, field_position[1] + field_height_arrows/2 - 25};

    // make field green if mode == selected mode, else make white
    if(selected_mode == modes[n_drawn_fields])
    {
      // draw field
      tft.drawRoundRect(field_position[0], field_position[1], field_width_arrows, field_height_arrows, field_corner_radius, ILI9341_GREEN);

      // add symbol
      // Upstairs
      if(n_drawn_fields==0){
        tft.drawBitmap(symbol_position[0],symbol_position[1],arrayOfModeSymbols[n_drawn_fields+5],50,50,ILI9341_GREEN);
      }
      // Downstairs
      else if(n_drawn_fields==1){
        tft.drawBitmap(symbol_position[0],symbol_position[1],arrayOfModeSymbols[n_drawn_fields+6],50,50,ILI9341_GREEN);
      }
    }
    else{
      // draw field
      tft.drawRoundRect(field_position[0], field_position[1], field_width_arrows, field_height_arrows, field_corner_radius, ILI9341_WHITE);

      // add symbol
      // Upstairs
      if(n_drawn_fields==0){
        tft.drawBitmap(symbol_position[0],symbol_position[1],arrayOfModeSymbols[n_drawn_fields+5],50,50,ILI9341_WHITE);
      }
      // Downstairs
      else if(n_drawn_fields==1){
        tft.drawBitmap(symbol_position[0],symbol_position[1],arrayOfModeSymbols[n_drawn_fields+6],50,50,ILI9341_WHITE);
      }
    }
  }


  // Status ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // update field positions
  field_position[0] = gap_between_fields;   // reset to gap_between_fields
  field_position[1] += field_height_arrows + gap_between_fields;

  // update text position
  text_width = ((status_str + status).length())*3*text_size;
  text_position[0] = field_position[0] + (2*field_width+gap_between_fields)/2 - text_width;
  text_position[1] = field_position[1] + field_height/2 - 7;

  // draw status field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_RISEORANGE);

  // write text
  tft.setTextColor(ILI9341_RISEORANGE);
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(status_str + status);


  // Last Mode ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  // update field position
  field_position[1] += field_height + gap_between_fields;

  // update text position
  text_width = ((last_mode_str + last_mode).length())*3*text_size;
  text_position[0] = field_position[0] + (2*field_width+gap_between_fields)/2 - text_width;
  text_position[1] = field_position[1] + field_height/2 - 7;

  // draw last mode field
  tft.drawRoundRect(field_position[0], field_position[1], 2*field_width+gap_between_fields, field_height, field_corner_radius, ILI9341_RISEORANGE);

  // write text
  tft.setCursor(text_position[0], text_position[1]);
  tft.setTextSize(text_size);
  tft.println(last_mode_str + last_mode);

}


#endif