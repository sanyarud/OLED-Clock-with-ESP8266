#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <Wire.h>
#include "SSD1306Wire.h"
#include "OLEDDisplayUi.h"
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Timezone.h>

// WiFi settings
const char* ssid = "Your_ssid";
const char* password = "Your_password";

// Define NTP client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Define your timezone (Kyiv, Ukraine)
TimeChangeRule myDST = {"EEST", Last, Sun, Mar, 2, 180};    // Daylight Saving Time rule
TimeChangeRule mySTD = {"EET", Last, Sun, Oct, 3, 120};     // Standard Time rule
Timezone myTZ(myDST, mySTD);

// Initialize the OLED display using Wire library
SSD1306Wire display(0x3c, 14, 12);
OLEDDisplayUi ui(&display);

// Define clock variables
int screenW = 128;
int screenH = 64;
int clockCenterX = screenW / 2;
int clockCenterY = screenH / 2;
int clockRadius = 23;

void digitalClockFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // Update time
  timeClient.update();
  time_t local_time = myTZ.toLocal(timeClient.getEpochTime());

  // Display digital clock
  String timenow = String(hour(local_time)) + ":" + String(minute(local_time)) + ":" + String(second(local_time));
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_24);
  display->drawString(clockCenterX + x , clockCenterY + y - 5, timenow ); 
  
  // Display "UKRAINE" text
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_24);
  display->drawString(clockCenterX + x , clockCenterY + y - 32, "UKRAINE" );
}

void dateFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // Update time
  timeClient.update();
  time_t local_time = myTZ.toLocal(timeClient.getEpochTime());

  // Display current date

  String datenow = String(day(local_time), DEC) + "-" + String(month(local_time), DEC) + "-" + String(year(local_time), DEC);

  // Get current day of the week
  String days[] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};
  int dayOfWeek = weekday(local_time);
  String dayOfWeekStr = days[dayOfWeek - 1];

  // Adjust font size and position
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->setFont(ArialMT_Plain_24); 
  display->drawString(clockCenterX + x , clockCenterY + y - 5, datenow ); 
  display->drawString(clockCenterX + x , clockCenterY + y - 32, dayOfWeekStr ); 
}

FrameCallback frames[] = { digitalClockFrame, dateFrame };
int frameCount = 2;
OverlayCallback overlays[] = { };
int overlaysCount = 0;

void setup() {
  Serial.begin(115200);
  delay(100);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Initialize NTP client
  timeClient.begin();

  // Initialize the OLED display
  ui.setTargetFPS(60);
  ui.setFrames(frames, frameCount);
  ui.setOverlays(overlays, overlaysCount);
  ui.init();

  display.flipScreenVertically();
}

void loop() {
  ui.update();
}
