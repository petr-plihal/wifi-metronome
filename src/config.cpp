#include "config.h"

// Nastavení připojení k WiFi síti
const char *ap_ssid = "Metronom";                   // Název vlastního přístupového bodu
const char *ap_password = "password";               // Heslo vlastního přístupového bodu

const char *wifi_ssid = "Poslední Wi-Fi na Zemi";   // Název existující WiFi sítě
const char *wifi_password = "ros665011166";         // Heslo existující WiFi sítě

const bool wifi_as_access_point = false;            // Připojení k existující WiFi síti (false) nebo vytvoření vlastního přístupového bodu (true)

WebServer server(80);                               // Webový server na portu 80


// Proměnné pro fungování metronomu
int buzzerInterval = 500;      // Interval spouštění bzučáku v milisekundách
int buzzerVolume = 128;        // "Hlasitost" (střída/PWM) bzučáku (0-255)
bool metronomeRunning = false; // Příznak běžícího metronomu