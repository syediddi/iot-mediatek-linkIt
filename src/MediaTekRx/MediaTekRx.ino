/*
  Web client

 This sketch connects to a website 
 using Wi-Fi functionality on MediaTek LinkIt platform.

 Change the macro WIFI_AP, WIFI_PASSWORD, WIFI_AUTH and SITE_URL accordingly.

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 modified 20 Aug 2014
 by MediaTek Inc.
 */

#include <LTask.h>
#include <LWiFi.h>
#include <LWiFiClient.h>
#include <ArduinoJson.h>

#define WIFI_AP "your ap"
#define WIFI_PASSWORD "your password"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
#define SITE_URL "your local server ip" //your nodejs or azure ip address or domain name

LWiFiClient c;



void setup()
{

  LWiFi.begin();
  Serial.begin(115200);



  // keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    delay(1000);
  }

  // keep retrying until connected to website
  Serial.println("Connecting to WebSite");
  while (0 == c.connect(SITE_URL, 3000))
  {
    Serial.println("Re-Connecting to WebSite");
    delay(1000);
  }

}

boolean disconnectedMsg = false;

void loop()
{
  // Make sure we are connected, and dump the response content to Serial
  while (!c)
  {
    Serial.println(" Server disconnected..");  
    // keep retrying until connected to website
    Serial.println("Connecting to WebSite");
    while (0 == c.connect(SITE_URL, 3000))
    {
      Serial.println("Re-Connecting to WebSite");
      delay(1000);    
    }
  }

  Serial.println(" Reading temperature..");
  updateTemperature();
  delay(3000);
  Serial.println("Detecting sound..");
  updateSound();
  delay(3000);
  Serial.println("Detecting person movement..");
  updatePIR();
  delay(3000);
  Serial.println("Detecting obstacle..");
  updateDistance();
  delay(3000);
  Serial.println("Updating device location..");
  updateGPSTracker();
  delay(3000);
  Serial.println("Calculating soil moisture..");
  updateMoisture();
  delay(3000);
  Serial.println("Detecting gas leakage..");
  updateGasLeak();
  delay(3000);
  Serial.println("Recording light intensity..");
  updateLightIntensity();
  delay(3000);
  updateLivingroomAttributes();
  delay(3000);
  updateBedroomAttributes();
  delay(3000);
}

void writeToConsole()
{
   // Make sure we are connected, and dump the response content to Serial
  while (c)
  {
    int v = c.read();
    if (v != -1)
    {
      Serial.print((char)v);
    }
  }

  Serial.println();
  Serial.println(" Server disconnected..");  
  // keep retrying until connected to website
  Serial.println("Connecting to WebSite");
  while (0 == c.connect(SITE_URL, 3000))
  {
      Serial.println("Re-Connecting to WebSite");
      delay(1000);    
   }
 }

void updatePIR()
{
  long unsigned int s;
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  JsonObject& desired = root.createNestedObject("desired");

  root["deviceid"] = "/iot/myhome/livingroom/pir";
  //assume default unit ms
  desired["motionstart"] = String(random(0,1000));
  desired["motionend"]= String(random(1000,10000));

  String len = String(root.measureLength());
  
  c.println("POST /iot/myhome/livingroom/pir HTTP/1.1");
  c.println("Host: " SITE_URL);
  c.println("Content-Type: application/json");
  c.println("Cache-Control: no-cache");
  c.print("Content-Length: ");
  c.println(len); 
  c.println("Connection: close");
  c.println();
  root.printTo(c);

  root.printTo(Serial);

   //logic to detect slow server response and post the request again without waiting for dead response
  s = millis();
  // waiting for server response
  Serial.println("waiting HTTP response:");
  while (!c.available())
  {
    delay(100);
    if((millis() - s > 3000))
    {
      Serial.println();
      Serial.println("Server not responding..");
      break;
    }
  }

 Serial.println("Calling write to console..");
 writeToConsole();
  }
void updateDistance()
{
  long unsigned int s;
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  JsonObject& desired = root.createNestedObject("desired");

  root["deviceid"] = "/iot/myhome/livingroom/distancesensor";
  //assume default unit cm
  desired["obstacle"]=String(random(50,450));

  String len = String(root.measureLength());
  
  c.println("POST /iot/myhome/livingroom/distance HTTP/1.1");
  c.println("Host: " SITE_URL);
  c.println("Content-Type: application/json");
  c.println("Cache-Control: no-cache");
  c.print("Content-Length: ");
  c.println(len); 
  c.println("Connection: close");
  c.println();
  root.printTo(c);

  root.printTo(Serial);

  s = millis();
  // waiting for server response
  Serial.println("waiting HTTP response:");
  while (!c.available())
  {
    delay(100);
    if((millis() - s > 3000))
    {
      Serial.println();
      Serial.println("Server not responding..");
      break;
    }
  }

 Serial.println("Calling write to console..");
 writeToConsole();
  
  }

void updateGPSTracker()
{
  long unsigned int s;
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  JsonObject& desired = root.createNestedObject("desired");

  root["deviceid"] = "/iot/mydevice";
  desired["lat"] =String(random(20,25));
  desired["long"]=String(random(22,27));

  String len = String(root.measureLength());
  
  c.println("POST /iot/mydevice/location HTTP/1.1");
  c.println("Host: " SITE_URL);
  c.println("Content-Type: application/json");
  c.println("Cache-Control: no-cache");
  c.print("Content-Length: ");
  c.println(len); 
  c.println("Connection: close");
  c.println();
  root.printTo(c);

  root.printTo(Serial);

  s = millis();
  
  // waiting for server response
  Serial.println("waiting HTTP response:");
  while (!c.available())
  {
    delay(100);

    if((millis() - s > 3000))
    {
      Serial.println();
      Serial.println("Server not responding..");
      break;
    }

    
  }

  Serial.println("Calling write to console..");
  writeToConsole();
}
void updateMoisture()
{
  long unsigned int s;
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  JsonObject& desired = root.createNestedObject("desired");

   root["deviceid"] = "/iot/myhome/garden/moisture";
  //assume default unit
  desired["moisture"] = String(random(40,60));

  String len = String(root.measureLength());
  
  c.println("POST /iot/myhome/garden/moisture HTTP/1.1");
  c.println("Host: " SITE_URL);
  c.println("Content-Type: application/json");
  c.println("Cache-Control: no-cache");
  c.print("Content-Length: ");
  c.println(len); 
  c.println("Connection: close");
  c.println();
  root.printTo(c);

  root.printTo(Serial);

  s = millis();
  
  // waiting for server response
  Serial.println("waiting HTTP response:");
  while (!c.available())
  {
    delay(100);

    if((millis() - s > 3000))
    {
      Serial.println();
      Serial.println("Server not responding..");
      break;
    }

    
  }

  Serial.println("Calling write to console..");
  writeToConsole();
  
}

void updateGasLeak()
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  
  JsonObject& desired = root.createNestedObject("desired");

  desired["leak"] = "no";
  root["deviceid"] = "/iot/myhome/kitchen/gas";
  
  long unsigned int s;

  String len = String(root.measureLength());
  
  c.println("POST /iot/myhome/kitchen/gas HTTP/1.1");
  c.println("Host: " SITE_URL);
  c.println("Content-Type: application/json");
  c.println("Cache-Control: no-cache");
  c.print("Content-Length: ");
  c.println(len); 
  c.println("Connection: close");
  c.println();
  root.printTo(c);

  root.printTo(Serial);

  s = millis();
  
  // waiting for server response
  Serial.println("waiting HTTP response:");
  while (!c.available())
  {
    delay(100);

    if((millis() - s > 3000))
    {
      Serial.println();
      Serial.println("Server not responding..");
      break;
    }

    
  }

  Serial.println("Calling write to console..");
  writeToConsole();

  }

void updateLightIntensity()
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  

  JsonObject& desired = root.createNestedObject("desired");

  desired["intensity"] = "80";
  root["deviceid"] = "/iot/myhome/livingroom/light";
  
  long unsigned int s;

  String len = String(root.measureLength());
  
  c.println("POST /iot/myhome/livingroom/light HTTP/1.1");
  c.println("Host: " SITE_URL);
  c.println("Content-Type: application/json");
  c.println("Cache-Control: no-cache");
  c.print("Content-Length: ");
  c.println(len); 
  c.println("Connection: close");
  c.println();
  root.printTo(c);

  root.printTo(Serial);

  s = millis();
  
  // waiting for server response
  Serial.println("waiting HTTP response:");
  while (!c.available())
  {
    delay(100);

    if((millis() - s > 3000))
    {
      Serial.println();
      Serial.println("Server not responding..");
      break;
    }

    
  }

  Serial.println("Calling write to console..");
  writeToConsole();

  }

void updateLivingroomAttributes()
{
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

   root["deviceid"] = "/iot/myhome/livingroom";
  

  JsonObject& desired = root.createNestedObject("desired");

  //Alternative api for loggin living room attributes all at once
  desired["window"] = "open";
  desired["door"] = "closed";
  desired["ac"] = "off";
  desired["temperature"] = String(random(24,28));
  desired["humidity"] = String(random(60,65));


  long unsigned int s;

  String len = String(root.measureLength());
  
  c.println("POST /iot/myhome/livingroom HTTP/1.1");
  c.println("Host: " SITE_URL);
  c.println("Content-Type: application/json");
  c.println("Cache-Control: no-cache");
  c.print("Content-Length: ");
  c.println(len); 
  c.println("Connection: close");
  c.println();
  root.printTo(c);

  root.printTo(Serial);

  s = millis();
  
  // waiting for server response
  Serial.println("waiting HTTP response:");
  while (!c.available())
  {
    delay(100);

    if((millis() - s > 3000))
    {
      Serial.println();
      Serial.println("Server not responding..");
      break;
    }

    
  }

  Serial.println("Calling write to console..");
  writeToConsole();


  
  } 

void updateBedroomAttributes()
{
   DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["deviceid"] = "/iot/myhome/bedroom";

  JsonObject& desired = root.createNestedObject("desired");

 //Alternative api for loggin living room attributes all at once
  desired["window"] = "open";
  desired["door"] = "closed";
  desired["ac"] = "off";
  desired["temperature"] = String(random(22,23));
  desired["humidity"] = String(random(75,80));

  long unsigned int s;

  String len = String(root.measureLength());
  
  c.println("POST /iot/myhome/bedroom HTTP/1.1");
  c.println("Host: " SITE_URL);
  c.println("Content-Type: application/json");
  c.println("Cache-Control: no-cache");
  c.print("Content-Length: ");
  c.println(len); 
  c.println("Connection: close");
  c.println();
  root.printTo(c);

  root.printTo(Serial);

  s = millis();
  
  // waiting for server response
  Serial.println("waiting HTTP response:");
  while (!c.available())
  {
    delay(100);

    if((millis() - s > 3000))
    {
      Serial.println();
      Serial.println("Server not responding..");
      break;
    }

    
  }

  Serial.println("Calling write to console..");
  writeToConsole();

  
  }  
void updateSound()
{
  long unsigned int s;
  long unsigned int e;
  
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  JsonObject& desired = root.createNestedObject("desired");
  desired["intensity"] = String(random(40,80));
  root["deviceid"] = "/iot/myhome/livingroom/mic";
  root["timeutc"] = "";
  root["signedby"]="";

  String len = String(root.measureLength());
  
  c.println("POST /iot/myhome/livingroom/mic HTTP/1.1");
  c.println("Host: " SITE_URL);
  c.println("Content-Type: application/json");
  c.println("Cache-Control: no-cache");
  c.print("Content-Length: ");
  c.println(len); 
  c.println("Connection: close");
  c.println();
  root.printTo(c);

  root.printTo(Serial);

  s = millis();
  // waiting for server response
  Serial.println("waiting HTTP response:");
  while (!c.available())
  {
    delay(100);
    if((millis() - s > 3000))
    {
      Serial.println();
      Serial.println("Server not responding..");
      break;
    }
  }

 Serial.println("Calling write to console..");
 writeToConsole();
}
void updateTemperature()
{

  long unsigned int s;
  long unsigned int e;
  
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  JsonObject& desired = root.createNestedObject("desired");
  desired["temperature"] = String(random(20,40));
  desired["humidity"]= String(random(60,80));

  root["deviceid"] = "/iot/myhome/livingroom/thermostat";
  root["timeutc"] = "";
  root["signedby"]="";

  String len = String(root.measureLength());
  
  c.println("POST /iot/myhome/livingroom/thermostat HTTP/1.1");
  c.println("Host: " SITE_URL);
  c.println("Content-Type: application/json");
  c.println("Cache-Control: no-cache");
  c.print("Content-Length: ");
  c.println(len); 
  c.println("Connection: close");
  c.println();
  root.printTo(c);

  root.printTo(Serial);

  s = millis();
  
  // waiting for server response
  Serial.println("waiting HTTP response:");
  while (!c.available())
  {
    delay(100);

    if((millis() - s > 3000))
    {
      Serial.println();
      Serial.println("Server not responding..");
      break;
    }

    
  }

  Serial.println("Calling write to console..");
  writeToConsole();
   
}

