# RISE UI - Exoskeleton UI ([TU Berlin RISE SoSe 2023](https://blogs.tu-berlin.de/mt_rise/en/home/))

<figure>
  <img src="Images/Main_UI_2.jpg" width=50%>
  <figcaption>Fig.1 - Main UI </figcaption>
</figure> 

## Project
* development of an UI for a 4-DOF lower limb exoskeleton
* UI contains 2 parts:

1. **Main UI** (communication to exo main controller via WiFi, see Fig.1)
2. **SACU** ("Single Actuator Control Unit") for manual control of actuators (see Fig.5)



## Firmware 
* UI Control with [Teensy 4.1](https://www.pjrc.com/store/teensy41.html)
* WiFi Connection with [ESP32 Adafruit Airlift](https://www.adafruit.com/product/4201)  
* programming via PlatformIO

### Structure
* see [Code/Flow_Chart](Code/Flow_Chart) for detailed code structure

<br>

* 2 buttons: TOGGLE button + SELECTION button
* 6 modes: WALK, SIDE STEP, STAND UP, SIT DOWN, UPSTAIRS, DOWNSTAIRS
* if last selection was SIT DOWN: only STAND UP as next mode possible
* if exo in standing position: every mode except STAND UP possible 

<br>

<figure>
  <img src="Images/Main_UI.jpg" width=50%>
  <figcaption>Fig.2 - Modes Exoskeleton </figcaption>
</figure> 

<br>
<br>


## EDA
* Schematics with Eagle 9.6.2
* SPI Communication Interfaces for Teensy-to-Wifi Module and Teensy-to-LCD  

### Components
* [Teensy 4.1](https://www.pjrc.com/store/teensy41.html)
* [Adafruit Airlift](https://www.adafruit.com/product/4201)
* [Piezo transducer](https://www.reichelt.com/de/en/shop/product/piezo_transducer_85_db_4_khz-35927) for acoustic feedback when mode is selected
* [2.4 inch LCD Display](https://www.waveshare.com/2.4inch-lcd-module.htm)
* [5000mAh Powerbank](https://www.intenso.de/produkte/powerbanks/xs5000-xs10000-xs20000/) for 5V power supply
* [Vibration Motor](https://www.reichelt.de/de/de/shop/produkt/dc-vibrationsmotor_3v_80ma_10000rpm-330549) for vibration feedback when toggling --> vibration with current from Teensy is too low, use [relay](https://www.christians-shop.de/1-Kanal-5V-Relay-Relais-Modul-10A-250VAC?gQT=1) + 5V powerbank instead
* LED @SACU: on when SACU on, blinking when motor active

<br>

<figure>
  <img src="Images/Blockschaltbild_Main_UI_final.png" width=50%>
  <figcaption>Fig.3 - Block Diagram Main UI </figcaption>
</figure> 

<br>
<br>
<br>

<figure>
  <img src="Images/Blockschaltbild_SACU_final.png" width=50%>
  <figcaption>Fig.4 - Block Diagram SACU </figcaption>
</figure> 

<br>
<br>

## 3D 
<figure>
  <img src="Images/SACU.jpg" width=50%>
  <figcaption>Fig.5 - 3D-printed SACU case </figcaption>
</figure> 


