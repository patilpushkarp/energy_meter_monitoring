//meter input
// declaration of variables pertaining to the energy meter 
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int  PulsePin = 8;     // the pin that the meter cal wire is attached to
const int ledPin = 13;       // the pin that the LED is attached to

int PulseCounter = 0;       // counter for the number of pulses
int State = 0;              // current state of the pulse
float rate = 3; 
float units = 0; 
float cost = 0;

// website 

#include<SoftwareSerial.h>
SoftwareSerial client(7,6); //Declaration of RX, TX for arduino
String webpage="";          //Initialization of the string data tp be displayed on the webpage
//Other essential declarations
int i=0,k=0;
String readString;
int x=0;
boolean No_IP=false;
String IP="";
char temp1='0';

// function to implement the ATtention commands and check the output of the commands     
void check4IP(int t1)
{
  int t2=millis();
  while(t2+t1>millis())
  {
    while(client.available()>0)
    {
      if(client.find("WIFI GOT IP"))
      {
        No_IP=true;
      }
    }
  }
}

//function to get the IP address of the wifi module
void get_ip()
{
  IP="";
  char ch=0;
  while(1)
  {
    Serial.println("getting ip");
    client.println("AT+CIFSR");       // AT command for generating the IP address of the module
    while(client.available()>0)
    {
      if(client.find("STAIP,"))
      {
        delay(3000);
        Serial.print("IP Address:");
        while(client.available()>0)
        {
          ch=client.read();
          if(ch=='+')
          break;
          IP+=ch;
        }
      }
      if(ch=='+')
      break;
    }
    if(ch=='+')
    break;
    delay(1000);
  }
  Serial.print(IP);
  Serial.print("Port:");
  Serial.println(80);
}

//Function for connecting the WiFi module with the WiFi 
void connect_wifi(String cmd, int t)
{
  int temp=0,i=0;
  while(1)
  {
    Serial.println(cmd);
    client.println(cmd); 
    while(client.available())
    {
      if(client.find("OK"))
      i=8;
    }
    delay(t);
    if(i>5)
    break;
    i++;
  }
  if(i==8)
  Serial.println("OK");
  else
  Serial.println("Error");
}

//Function to Initialize of the WiFi module
void wifi_init()
{
      connect_wifi("AT",1500);
      connect_wifi("AT+CWMODE=3",100);     //AT command for setting the operation mode of WiFi module
      connect_wifi("AT+CWQAP",100);        //AT command for quitting the connection with current access point
      connect_wifi("AT+RST",5000);         //AT command for resetting the module for setting up the new connection
      check4IP(5000);
      if(!No_IP)
      {
        Serial.println("Connecting Wifi....");
        connect_wifi("AT+CWJAP=\"<insert name of access point or router>\",\"<insert wifi password>\"",7000);         //AT command for connecting the WiFi
      }
      else
        {
        }
      Serial.println("Wifi Connected"); 
      get_ip();
      connect_wifi("AT+CIPMUX=1",100);          //AT command for setting the ID of the module
      connect_wifi("AT+CIPSERVER=1,80",100);    //AT command for setting up the server mode and the initialization of the port 80
}

//Function to send the data from the server to the client
void sendwebdata(String webPage)
{
    int ii=0;
     while(1)
     {
      unsigned int l=webPage.length();          //Count the size of the file to be transmitted from the server to client
      Serial.print("AT+CIPSEND=0,");            //AT command to send the data from ESP module to web address
      client.print("AT+CIPSEND=0,");
      Serial.println(l+2);
      client.println(l+2);
      delay(100);
      Serial.println(webPage);
      client.println(webPage);
      while(client.available())
      {
        if(client.find("OK"))
        {
          ii=11;
          break;
        }
      }
      if(ii==11)
      break;
      delay(100);
     }
}

//Function to setup the arduino
void setup() {
   // meter setup
   pinMode(PulsePin, INPUT);
   pinMode(ledPin, OUTPUT);
   lcd.begin(16, 2);               //Initialization of the 16x2 LCD display
   lcd.print("no. of pulses=");
   Serial.begin(115200);           //Setting of the baud rate of operation

   //website setup
   client.begin(115200);
   wifi_init();
   Serial.println("System Ready..");
   
}

//Function for calculating the necessary values continuously
void loop() {
  //meter
  lcd.setCursor(14, 0);
  State = digitalRead(PulsePin);
  digitalWrite(ledPin,State);
   if (State == LOW) {
    PulseCounter++;
    units = PulseCounter/5;                   //Calculation of number of units
    cost = rate*units;                        //Calculation of the cost
    lcd.print(PulseCounter);
    delay(300);    
   }
  
  //Following code checks the availability of the client
  k=0;
  //Serial.println("Please Refresh your Page");
  while(k<1)
  {
    k++;
   while(client.available())
   {
    if(client.find("0,CONNECT"))
    {
      Serial.println("Start Printing");
      Send();
      Serial.println("Done Printing");
      delay(1000);
    }
  }
  delay(1);
 } 
}


//Function for display of the data on the website
void Send()
{
      //webpage = "<h1>Welcome to your energy meter reading</h1><body bgcolor=f0f0f0>";
      //sendwebdata(webpage);
      String pulse1=String(PulseCounter);
      webpage = "<p>No. of pulses = " + pulse1 +"</p>";             //Required HTML code
      sendwebdata(webpage);
      String unitcount=String(units);
      webpage = "<p>No of units = " + unitcount +"</p>";            //Required HTML code
      sendwebdata(webpage);
      String cost1=String(cost);
      webpage = "<p>Total Bill = Rs. " + cost1 +"</p>";             //Required HTML code
      sendwebdata(webpage);
      delay(1000);
     
     client.println("AT+CIPCLOSE=0");                //AT command to close the connection
}
