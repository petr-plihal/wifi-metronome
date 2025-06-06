# Metronom na ESP32

Tento projekt implementuje metronom na mikrokontroléru ESP32 s webovým rozhraním pro nastavení BPM (beats per minute) a hlasitosti bzučáku.

## Funkce

- Připojení k WiFi síti nebo vytvoření vlastního přístupového bodu
- Webový server pro ovládání metronomu
- Nastavení BPM (40-240)
- Nastavení hlasitosti bzučáku (0-255 (PWM) - na stránce v %)
- Start/Stop metronomu

## Hardware

- ESP32
- Bzučák a dioda připojené k pinu 23

## Použité knihovny

- Arduino
- WiFi
- WebServer
- driver/timer (pro práci s časovačem)

## Nastavení a spuštění

1. Zapojte bzučák (nebo i LED) k pinu 23 (lze změnit v souboru `src/config.h`)

2. V souboru `src/config.cpp` 
    - Vyberte metodu připojení `wifi_as_access_point`
    - Zadejte jméno a heslo pro vlastní přístupový bod `ap_ssid`, `ap_password`, nebo vyplňte jméno a heslo pro připojení k WiFi síti `wifi_ssid`, `wifi_password`
    - Nastavte port pro webový server `WebServer server(XX);`

3. Nahrání kódu na ESP32

4. Připojení k WiFi síti nebo k vytvořenému přístupovému bodu
    - V konzoli se zobrazí IP adresa, na které je dostupné webové rozhraní

5. Otevřete webový prohlížeč a zadejte IP adresu z konzole

## Poznámky k používání

 - Start/Stop metronomu tlačítkem `Start/Stop`

 - Nastavení hlasitosti a BPM pomocí posuvných lišt, nebo textových polí

 - Změny provedené na posuvné liště se projeví ihned

 - Změny zadané do textového pole se projeví po stisknutí tlačítka `Nastav`

## Struktura zdrojových souborů
 - `src/main.cpp` - hlavní nekonečná smyčka a volání funkcí pro obsluhu webového serveru
 - `src/config.h`, `src/config.cpp` - konfigurační soubor pro nastavení WiFi, pinu bzučáku a portu webového serveru
 - `src/timer.h`, `src/timer.cpp` - obsluha časovače pro generování tónu
 - `src/web_server.h`, `src/web_server.cpp` - obsluha webového serveru - zpracování požadavků a spouštění potřebných funkcí
 - `src/web_pages.h`, `src/web_pages.cpp` - HTML stránka pro ovládání metronomu

## Známé problémy

 - Při změně BPM a hlasitosti se může stát, že se tón zastaví a znovu spustí až po uplynutí jednoho taktu

## Možná vylepšení

 - Přidání možnosti změny tónu bzučáku (BPM také ovlivňuje tón)
 
 - Přidání "presets" pro různé takty (4/4, 3/4, 6/8, ...)
 
 - Přidání hlasitějšího zvuku prvního taktu
