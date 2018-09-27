
#include <SPI.h>
#include <ESP8266WiFi.h>

const char* ssid = "ManjCell";
const char* password = "welcome@123";

const char* host = "smartgatedemo.azurewebsites.net";
const int httpsPort = 80; 
// Each team should change the value of the below value (between 1 to 6)
String ApplicationInstanceId = "1";
//http://smartgatedemo.azurewebsites.net/SampleIoT/GetUserName

WiFiClient client;
//Wifi Details Ends Here
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
long customtime = 0;         // the last time the output pin was toggled
long debounce = 200; 

#define led 13 //GPIO13 is connected to + of LED (long leg), GND of ESP8266 is connected to - of LED (short leg)

void setup() {
    Serial.begin(9600);
   pinMode(led, OUTPUT); 
  
  // Connect to wifi Starts From Here
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // Connect to wifi Starts Ends Here
}

void loop()
{     
     String url = "/api/SampleIoTServices/GetUserName?applicationInstanceId=" + ApplicationInstanceId;
     delay(7000);
 }
            
//Call api and send data.
String PostDataToEndPoint(String Url)
{
   // Use WiFiClientSecure class to create TLS connection
  WiFiClient client;
  Serial.print("connecting to ");
  Serial.println(host);
  Serial.println("Port is :");
  Serial.println(httpsPort);
  
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
  }
  Serial.println("requesting URL: ");
      Serial.println(Url);
    
      client.print(String("GET ") + Url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "User-Agent: BuildFailureDetectorESP8266\r\n" +
                   "Connection: close\r\n\r\n");
    
      Serial.println("request sent");
      while (client.connected()) {
        String line = client.readStringUntil('\n');
        if (line == "\r") {
          Serial.println("headers received");
          break;
        }
      }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("Response is:");
  Serial.println("----***-----***-----***-----***-----***-----***-----***-----");
  Serial.println(line);
  Serial.println("----***-----***-----***-----***-----***-----***-----***-----");
  Serial.println("closing connection");
  return "\r";
}
