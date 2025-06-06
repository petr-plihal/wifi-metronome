#include "web_pages.h"

const char* main_page = R"rawliteral(
<!DOCTYPE html>
<html lang="cs" encoding="utf-8">
<head>
    <meta charset="UTF-8">
    <title>Metronom</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; }
        .slider { width: 300px; }
    </style>
</head>
<body>

    <h1>Nastavení metronomu</h1>
    
    <!-- Ovládání hlasitosti -->
    <label for="volume">Hlasitost:</label>
    <input type="range"  id="volume"      name="volume"      min="0" max="100" class="slider" oninput="updateVolume(this.value)">
    <input type="number" id="volumeInput" name="volumeInput" min="0" max="100" value="50">
    <button onclick="updateVolume(document.getElementById('volumeInput').value)">Nastav</button>
    <p>Hlasitost: <span id="volumeValue">50</span>%</p>
    
    <!-- Ovládání BPM -->
    <label for="bpm">Tempo (BPM):</label>
    <input type="range"  id="bpm"      name="bpm"      min="40" max="240" class="slider" oninput="updateBPM(this.value)">
    <input type="number" id="bpmInput" name="bpmInput" min="40" max="240" value="120">
    <button onclick="updateBPM(document.getElementById('bpmInput').value)">Nastav</button>
    <p>BPM: <span id="bpmValue">120</span></p>
    
    <!-- Tlačítko pro spuštění/zastavení metronomu -->
    <button id="toggleMetronome" onclick="toggleMetronome()">Start</button>
    
    <script>

        // Aktualizace hlasitosti
        function updateVolume(value) {

            if (value < 0) value = 0;
            if (value > 100) value = 100;

            document.getElementById('volumeValue').innerText = value;
            document.getElementById('volume').value = value;
            document.getElementById('volumeInput').value = value;

            var pwmValue = Math.round(value * 2.55); // Převod procent na hodnoty PWM (0-255)
            var xhr = new XMLHttpRequest();

            xhr.open("GET", "/setVolume?value=" + pwmValue, true);
            xhr.send();

            xhr.onload = function() {
                if (xhr.status === 200) { // Kontrola návratového kódu
                    console.log("Hlasitost nastavena na " + value + "%");
                } else {
                    console.error("Chyba při nastavení hlasitosti: " + xhr.status);
                }
            };
            
        }

        // Aktualizace BPM (úderů za minutu)
        function updateBPM(value) {

            if (value < 40) value = 40;
            if (value > 240) value = 240;

            document.getElementById('bpmValue').innerText = value;
            document.getElementById('bpm').value = value;
            document.getElementById('bpmInput').value = value;

            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/setBPM?value=" + value, true);
            xhr.send();

            xhr.onload = function() {
                if (xhr.status === 200) { // Kontrola návratového kódu
                    console.log("BPM nastaveno na " + value);
                } else {
                    console.error("Chyba při nastavení BPM: " + xhr.status);
                }
            };

        }

        // Přepínání metronomu (spuštění/zastavení)
        function toggleMetronome() {

            var button = document.getElementById('toggleMetronome');
            button.disabled = true;

            var xhr = new XMLHttpRequest();

            xhr.open("GET", "/toggleMetronome", true);
            xhr.send();

            xhr.onload = function() {

                button.disabled = false;

                if (xhr.status === 200) { // Kontrola návratového kódu
                    if (xhr.responseText === "Start") {

                        button.innerText = "Stop";
                        console.log("Metronom spuštěn");

                    } else {

                        button.innerText = "Start";
                        console.log("Metronom zastaven");

                    }
                } else {
                    console.error("Chyba při přepínání metronomu: " + xhr.status);
                }
            };
        }
    </script>

</body>
</html>
)rawliteral";