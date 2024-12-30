# RISE UI - Exoskeleton UI ([TU Berlin RISE SoSe 2023](https://blogs.tu-berlin.de/mt_rise/en/home/))

<figure>
  <img src="Images/Main_UI_2.jpg" width=50%>
  <figcaption>Fig.1 - Main UI </figcaption>
</figure> 

## Project
* development of an UI for a 4-DOF lower limb exoskeleton 
* communication to exo main controller via WiFI (ESP32 Adafruit Airlift Module)
* "Single Actuator Control Unit" (SACU) for manual control of actuators



## Firmware 
* UI Control with Teensy 4.1
* WiFi Connection with ESP32 Adafruit Airlift Module 
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


