#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "wifi_name";
const char* password = "12345678";
const char* serverIP = "laptop_wifi_adapter_IP";
const int serverPort = 1234;

WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(10);

  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
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
}

void loop() {
  if (Serial.available() > 0) {
    int distance = Serial.parseInt(); // Read the distance data sent by Arduino Uno
    
    // Check if the distance is within a reasonable range (0-400 cm)
    if (distance >= 0 && distance <= 400) {
      sendToLaptop(distance);
    } else {
      Serial.println("Invalid distance value: " + String(distance));
    }
  }
}

void sendToLaptop(int distance) {
  if (!client.connected()) {
    if (!client.connect(serverIP, serverPort)) {
      Serial.println("Connection failed");
      delay(5000);
      return;
    }
  }

  client.println(distance); // Sending data with println() to indicate end of message

  // Wait a short while before sending more data
  delay(100);
}
