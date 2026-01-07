#include <WiFi.h>

// APNA WIFI KA NAAM AUR PASSWORD YAHAN DALO
const char* ssid = "Rana Waqas";          // WiFi name
const char* password = "60309016";   // WiFi password

void setup() {
  // Serial monitor start karo
  Serial.begin(115200);
  delay(2000);  // Thora wait karo
  
  Serial.println("      ESP32 WIFI TEST PROGRAM");
  
  // WiFi connect karne ki koshish
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  // Wait karo connection ke liye
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;
    
    if (attempts > 30) {  // 15 seconds ke baad stop
      Serial.println("\nWiFi Connection Failed!");
      Serial.println("Please check:");
      Serial.println("1. WiFi name and password");
      Serial.println("2. WiFi range");
      Serial.println("3. Mobile hotspot use karo agar problem ho");
      while(1);  // Stop here
    }
  }
  
  // Agar connection successful ho gaya
  Serial.println("\n WIFI CONNECTED SUCCESSFULLY!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Signal Strength (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void loop() {
  // Sirf WiFi status check karo har 10 seconds
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi Connected | IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println(" WiFi Disconnected!");
  }
  
  delay(10000);  // 10 seconds wait
}




