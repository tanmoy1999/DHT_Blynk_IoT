#define BLYNK_PRINT Serial   
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "CPQEcR5CPdd9SUo39yZ3qR-8w9Fbg8KO"; //Enter the Auth code which was send by Blink

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "D-Link_DIR-600M";                  //Enter your WIFI SSID
char pass[] = "alliswell";                        //Enter your WIFI Password

#define DHTPIN 0                                  // Digital pin 4

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

int led=0;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    digitalWrite(led,HIGH);
    return;
  }
  else
  {
    // You can send any value at any time.
    // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V5, h);  //V5 is for Humidity
    Blynk.virtualWrite(V6, t);  //V6 is for Temperature
    digitalWrite(led,LOW);  
  }
}

void setup()
{
  Serial.begin(9600);                                                                   // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(60000L, sendSensor);
}

void loop()
{
  
  Blynk.run(); // Initiates Blynk APP and server
  timer.run(); // Initiates SimpleTimer
}
