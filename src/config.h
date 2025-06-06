#ifndef CONFIG_H
#define CONFIG_H

#include <WebServer.h>

// Parametry bzučáku

#define BUZZER_PIN 23  // Pin připojený k bzučáku
#define CHANNEL 0      // PWM kanál
#define RESOLUTION 8   // Rozlišení PWM (8 bitů = 0–255)
#define FREQ 2000      // Frekvence bzučáku v Hz


// Nastavení připojení k WiFi síti

extern const char *ap_ssid;
extern const char *ap_password;

extern const char *wifi_ssid;
extern const char *wifi_password;

extern const bool wifi_as_access_point;

extern WebServer server;


// Proměnné pro nastavení metronomu

extern int buzzerInterval;
extern int buzzerVolume;


// Proměnné pro dočasné řešení

extern unsigned long interval;
extern unsigned long previousMillis;
extern bool metronomeRunning;


#endif // CONFIG_H