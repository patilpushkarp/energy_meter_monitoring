# Energy Meter Monitoring Using Internet of Things

## About Project

<p align="justify">Energy meters are used to measure the consumption of the electrical energy by industries and residential areas. Authorities were setup to keep the track of the energy consumption by the consumers. They employed people to get the photographs of the energy meter reading as a proof to the consumer that they are charging the latter proportionate to the electrical energy consumed by them. These meters were analog in nature and hence inherently inefficient and not tamper-proof. With the advancement in the technology, digital meters were introduced which are fast and more efficient than the analog meters. The problems arose when the number of industries and residential increased to accommodate the population and the authorities which used to keep a track on the energy consumption had to employ more number of people to get the photographs of the meter reading, thus increasing the labor cost. The process also led to the delay in the acquisition of data for processing and further delay in providing that data to the consumer. So in this project we made an attempt to reduce the labor and accelerate the process of data acquisition with the help of Internet of Things. The main aim of this project is to build a smart energy monitoring meter to create transparency for the consumers and change the conventional method of billing.</p>

## Components Required

|Components|Model|
|---|---|
|Energy meter|Jaipur AC Single Phase Energy Meter|
|Arduino|Arduino Uno|
|Wifi Module|ESP8266-01|
|LCD display|LCD 16x2 Display|
|Voltage regulator|LD33V3|

## Block Diagram

<p align="center">
  <img src="https://user-images.githubusercontent.com/16013308/42421594-ab0834b0-82f5-11e8-832c-6b0ec53e0275.png"/></p>

## Connections

### ESP8266-01 connections

#### With LD33V3 (Voltage Regulator)
|ESP8266-01|LD33V3|
|---|---|
|VCC|Output|
|GND|GND|

#### With Arduino
|Arduino|ESP8266-01|
|---|---|
|Tx|Tx|
|Rx|Rx|
|GND|GND|

Rest of the pins of ESP8266-01 be left unconnected.


### LDR Connections

#### With Arduino
|Arduino|LDR|
|---|---|
|5V|VCC|
|GND|GND|
|Pin 8|DO|

## Set-up

1. Connect the components as per the block diagram and aforementioned tables
2. Place LDR near the blinking LED of Meter in a black-box to avoid interfernce from outside light 
3. Run the arduino code present in the Arduino folder named final.ino
4. Access the information using website
