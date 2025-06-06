#ifndef WEB_SERVER_H
#define WEB_SERVER_H

// Nastaví a pokusí se o připojení k WiFi - podle konfigurace v config.h (přístupový bod nebo existující síť)
void setupWifiConnection();

// Nastaví a pokusí se spustit webový server - obsluha jednotlivých endpointů
void setupWebServer();      


// Obsluha endpointu "/" - hlavní stránka s ovládáním metronomu
void handleRoot();

// Obsluha endpointu "/setVolume" - nastavení hlasitosti bzučáku
void handleSetVolume();

// Obsluha endpointu "/setBPM" - nastavení BPM (tempa)
void handleSetBPM();

// Obsluha endpointu "/toggleMetronome" - přepínání metronomu (start/stop)
void handleToggleMetronome();


#endif // WEB_SERVER_H