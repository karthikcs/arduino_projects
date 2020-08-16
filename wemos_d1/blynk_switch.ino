#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const char* ssid = "Ch**i";
const char* password = "s***4u";
int ledPin = D4;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "3d6***************************20";

WiFiServer server(8181);

IPAddress ip(192, 168, 1, 90);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 0, 1);


void setup(){
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin, LOW);

  //COnnect to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(ip, gateway, subnet, dns);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi Connected");

  server.begin();
  Serial.println("Server Started");
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  
  //Blynk.begin(auth, ssid, password);
  Blynk.config(auth);
  //Blynk.begin(auth, ssid, password, "blynk-cloud.com", 8442);
}

void loop(){
  
  delay(10);
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    //Serial.println("No Client found");
    Blynk.run();
    return ;
  }
  else {
    // Wait until the client sends some data
  Serial.println("New client");
  while(!client.available()){
    Serial.println("Client not available");
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  int value = LOW;
  int i = request.indexOf("/LED=ON");
  Serial.println(i);
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
  // Response to client
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("Love Wemos D1 Mini");
  client.println("</html>");
  
  }
  
  
  //Blynk.run();
}
