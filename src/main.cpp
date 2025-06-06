#include <Arduino.h>

#include "config.h"
#include "web_server.h"
#include "timer.h"


// Inicializační funkce - nastavení pinů, PWM a sériové komunikace
void setup() {

    Serial.begin(115200); // Inicializace sériové komunikace - rychlost 115200 baudů
    ledcSetup(CHANNEL, FREQ, RESOLUTION); // Nastavení PWM - frekvence a rozlišení (8 bitů)
    ledcAttachPin(BUZZER_PIN, CHANNEL);   // Připojení pinu bzucáku k PWM kanálu

    setupTimer();
    setupWifiConnection();
    setupWebServer();
}

// Hlavní smyčka programu - obsluha web serveru
void loop() {

    server.handleClient();

    // Periodické bzučení/údery metronomu
    if (metronomeRunning && tickFlag) {

        tickFlag = false;                 // Resetování příznaku tiknutí časovače

        ledcWrite(CHANNEL, buzzerVolume); // Bzučení na zadanou hlasitost
        delay(100);                       // Délka zvuku v milisekundách
        ledcWrite(CHANNEL, 0);            // "Vypnutí" bzučáku
    }

}