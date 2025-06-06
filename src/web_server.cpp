#include "config.h"
#include "web_server.h"
#include "web_pages.h"
#include "timer.h"
#include "main.h"

/** Zdroje:
 *  - https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi/examples
 */


void setupWifiConnection() {

    if (wifi_as_access_point) {

        WiFi.softAP(ap_ssid, ap_password); // Vytvoření přístupového bodu

        Serial.println();
        Serial.println("Přístupový bod úspěšně vytvořen, detail připojení:");
        Serial.println("Název:          " + String(ap_ssid));
        Serial.println("Heslo:          " + String(ap_password));
        Serial.println();

    } else {

        WiFi.begin(wifi_ssid, wifi_password); // Připojení k existující WiFi síti

        // Čekání na připojení k WiFi síti (žádný timeout!)
        while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.println("Připojování k WiFi...");
        }

        Serial.println();
        Serial.println("Úspěšně připojeno k WiFi, detail připojení:");
        Serial.println("Název:          " + String(wifi_ssid));
        Serial.println("Heslo:          " + String(wifi_password));
        Serial.println();
    }
}


void setupWebServer() {

    // Nastavení obsluhy jednotlivých endpointů
    server.on("/", handleRoot);
    server.on("/setVolume", handleSetVolume);
    server.on("/setBPM", handleSetBPM);
    server.on("/toggleMetronome", handleToggleMetronome);

    server.begin(); // Spuštění serveru

    Serial.println("Webový server spuštěn na adrese " + WiFi.localIP().toString());
}


void handleRoot() {
    server.send(200, "text/html", main_page);
}


void handleSetVolume() {

    // Přijatá hodnota hlasitosti musí být v rozmezí 0-255
    if (server.hasArg("value")) {

        int desiredVolume = server.arg("value").toInt();

        if (desiredVolume >= 0 && desiredVolume <= 255) {

            buzzerVolume = desiredVolume;
            server.send(200, "text/plain", "Volume set to " + String(buzzerVolume));

        } else {
            server.send(400, "text/plain", "Špatná hodnota hlasitosti");
        }

        Serial.println("Hlasitost nastavena na " + String(buzzerVolume));

    } else {
        server.send(400, "text/plain", "Bad Request");
    }
}


void handleSetBPM() {

    // Přijatá hodnota BPM musí být v rozmezí 40-240 (vybrané pro účely metronomu - lze změnit) 
    if (server.hasArg("value")) {

        int bpm = server.arg("value").toInt();

        if (bpm >= 40 && bpm <= 240) {

            // Jedna minuta má 60 000 milisekund - interval mezi údery pro časovač je tedy 60 000 / BPM (výsledek v milisekundách)
            buzzerInterval = 60000 / bpm;
            updateTimerInterval();
            server.send(200, "text/plain", "BPM set to " + String(bpm));

        } else {
            server.send(400, "text/plain", "Invalid BPM value");
        }

        Serial.println("BPM nastaveno na " + String(bpm));

    } else {
        server.send(400, "text/plain", "Bad Request");
    }

    
}


void handleToggleMetronome() {

    tickFlag = false; // Při zastavení metronomu vymazat příznak tiknutí (mohl zůstat z předchozího běhu)

    metronomeRunning = !metronomeRunning;

    if (metronomeRunning) {
        server.send(200, "text/plain", "Start");
    } else {
        server.send(200, "text/plain", "Metronome stopped");
    }

    Serial.println("Metronom přepnut na " + String(metronomeRunning));
}