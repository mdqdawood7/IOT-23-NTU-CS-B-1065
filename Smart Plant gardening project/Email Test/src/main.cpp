// #include <WiFi.h>
// #include <ESP_Mail_Client.h>

// // ===== WiFi =====
// const char* ssid = "Adeel Home";
// const char* password = "aqeel@0059";

// // ===== Gmail SMTP =====
// #define SMTP_HOST "smtp.gmail.com"
// #define SMTP_PORT 465

// #define AUTHOR_EMAIL "ranahamadrajpoot003@gmail.com"
// #define AUTHOR_PASSWORD "xjaw ukki hwmn mwds"
// #define RECIPIENT_EMAIL "ranahamadrajpoot003@gmail.com"

// SMTPSession smtp;

// void setup() {
//   Serial.begin(115200);
//   delay(1000);

//   // WiFi connect
//   WiFi.begin(ssid, password);
//   Serial.print("Connecting to WiFi");
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("\nWiFi connected");

//   // SMTP config
//   ESP_Mail_Session session;
//   session.server.host_name = SMTP_HOST;
//   session.server.port = SMTP_PORT;
//   session.login.email = AUTHOR_EMAIL;
//   session.login.password = AUTHOR_PASSWORD;
//   session.login.user_domain = "";

//   SMTP_Message message;
//   message.sender.name = "Smart Plant System";
//   message.sender.email = AUTHOR_EMAIL;
//   message.subject = "Plant Water Alert";
//   message.addRecipient("Owner", RECIPIENT_EMAIL);
//   message.text.content = "Plant needs water. Please check.";

//   if (!smtp.connect(&session)) {
//     Serial.println("SMTP connection failed");
//     return;
//   }

//   if (!MailClient.sendMail(&smtp, &message)) {
//     Serial.println("Email send failed");
//   } else {
//     Serial.println("Email sent successfully!");
//   }
// }

// void loop() {
// }
/////////////////////////////////////////////////////////////////
//////////////sensor testing//////////////////

// #include <Arduino.h>

// const int soilPin = 34;   // AO pin connected here

// void setup() {
//   Serial.begin(115200);
//   delay(1000);

//   Serial.println("Soil Moisture Sensor Test");
// }

// void loop() {
//   int soilValue = analogRead(soilPin);

//   Serial.print("Soil Value: ");
//   Serial.println(soilValue);

//   delay(1000); // 1 second gap
// }




////////////////////////////////////////////////////////
///////////////sensor plus email testing///////////////

// #include <WiFi.h>
// #include <ESP_Mail_Client.h>

// // ===== FUNCTION PROTOTYPE =====
// void sendEmail();

// // ===== WIFI DETAILS =====
// const char* ssid = "Adeel Home";
// const char* password = "aqeel@0059";

// // Gmail SMTP
// #define SMTP_HOST "smtp.gmail.com"
// #define SMTP_PORT 465
// #define AUTHOR_EMAIL "ranahamadrajpoot003@gmail.com"
// #define AUTHOR_PASSWORD "xjaw ukki hwmn mwds"
// #define RECIPIENT_EMAIL "ranahamadrajpoot003@gmail.com"

// // ===== SOIL SENSOR =====
// #define SOIL_PIN 34
// #define THRESHOLD 1500     // adjust after testing

// bool alertSent = false;   // spam control
// SMTPSession smtp;

// void setup() {
//   Serial.begin(115200);
//   delay(1000);

//   // WiFi connect
//   Serial.print("Connecting to WiFi");
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("\nWiFi connected");

//   pinMode(SOIL_PIN, INPUT);
// }

// void loop() {
//   int soilValue = analogRead(SOIL_PIN);
//   Serial.print("Soil Value: ");
//   Serial.println(soilValue);

//   // Soil dry + send email once
//   if (soilValue > THRESHOLD && !alertSent) {
//     sendEmail();
//     alertSent = true;
//   }

//   // Soil wet + reset alert
//   if (soilValue <= THRESHOLD) {
//     alertSent = false;
//   }

//   delay(2000); // read every 2 seconds
// }

// // ===== EMAIL FUNCTION =====
// void sendEmail() {

//   ESP_Mail_Session session;
//   session.server.host_name = SMTP_HOST;
//   session.server.port = SMTP_PORT;
//   session.login.email = AUTHOR_EMAIL;
//   session.login.password = AUTHOR_PASSWORD;
//   session.login.user_domain = "";

//   SMTP_Message message;
//   message.sender.name = "Smart Plant System";
//   message.sender.email = AUTHOR_EMAIL;
//   message.subject = "Plant Water Alert";
//   message.addRecipient("Owner", RECIPIENT_EMAIL);
//   message.text.content = "Plant needs water. Please water the plant.";

//   if (!smtp.connect(&session)) {
//     Serial.println("SMTP connection failed");
//     return;
//   }

//   if (!MailClient.sendMail(&smtp, &message)) {
//     Serial.println("Email send failed");
//   } else {
//     Serial.println("Email sent successfully!");
//   }
// }

/////////////////////////////////////////////////////
/////////////////Final code with blynk///////////////

/************ BLYNK CONFIG ************/
#define BLYNK_TEMPLATE_ID "TMPL6WpsGzpqZ"
#define BLYNK_TEMPLATE_NAME "Water Plant"
#define BLYNK_AUTH_TOKEN "TszksukMEOOA3d_sjAlyoIU-F9plZ2vo"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP_Mail_Client.h>

/************ WIFI DETAILS ************/
char ssid[] = "Adeel Home";
char pass[] = "aqeel@0059";

/************ EMAIL (SMTP) DETAILS ************/
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "ranahamadrajpoot003@gmail.com"
#define AUTHOR_PASSWORD "xjaw ukki hwmn mwds"
#define RECIPIENT_EMAIL "ranahamadrajpoot003@gmail.com"

/************ PIN DEFINITIONS ************/
#define SOIL_PIN 34
#define RELAY_PIN 26        // Active LOW relay

/************ OBJECTS ************/
SMTPSession smtp;
BlynkTimer timer;

/************ VARIABLES ************/
bool emailSent = false;
bool pumpOn = false;

/************ EMAIL FUNCTION ************/
void sendEmailAlert() {
  ESP_Mail_Session session;
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;

  SMTP_Message message;
  message.sender.name = "Smart Plant System";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "🌱 Plant Needs Water!";
  message.addRecipient("Owner", RECIPIENT_EMAIL);
  message.text.content =
      "Soil is dry.\nPlease open Blynk app and turn ON the water pump.";

  if (!smtp.connect(&session)) {
    Serial.println("SMTP connection failed");
    return;
  }

  if (MailClient.sendMail(&smtp, &message)) {
    Serial.println("Email sent successfully");
  } else {
    Serial.println(" Email sending failed");
  }

  smtp.closeSession();
}

/************ BLYNK BUTTON (PUMP CONTROL) ************/
// Button Widget → V2 → SWITCH MODE
BLYNK_WRITE(V2) {
  int value = param.asInt();

  if (value == 1) {
    pumpOn = true;
    digitalWrite(RELAY_PIN, LOW);   // Pump ON
    Serial.println(" Pump ON (Blynk)");
  } else {
    pumpOn = false;
    digitalWrite(RELAY_PIN, HIGH);  // Pump OFF
    Serial.println("Pump OFF (Blynk)");
  }
}

/************ SOIL CHECK ************/
void checkSoil() {
  int soilValue = analogRead(SOIL_PIN);

  Serial.print("Soil Value: ");
  Serial.println(soilValue);

  // Show soil value on Gauge → V0
  Blynk.virtualWrite(V0, soilValue);

  // DRY soil
  if (soilValue > 1500) {
    Blynk.virtualWrite(V1, 255); // LED ON

    if (!emailSent) {
      sendEmailAlert();
      emailSent = true;
    }
  }
  // WET soil
  else {
    Blynk.virtualWrite(V1, 0); // LED OFF
    emailSent = false;

    if (pumpOn) {
      digitalWrite(RELAY_PIN, HIGH); // Auto OFF pump
      pumpOn = false;
      Blynk.virtualWrite(V2, 0);
      Serial.println("🌧 Soil wet → Pump AUTO OFF");
    }
  }
}

/************ SETUP ************/
void setup() {

  // 🔒 BOOT SAFETY (MOST IMPORTANT FIX)
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);   // FORCE pump OFF at power ON
  delay(1000);                     // Boot stabilization

  Serial.begin(115200);

  pinMode(SOIL_PIN, INPUT);

  // WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n WiFi Connected");

  // Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Timer
  timer.setInterval(3000L, checkSoil);
}

/************ LOOP ************/
void loop() {
  Blynk.run();
  timer.run();
}













