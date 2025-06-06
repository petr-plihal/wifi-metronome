#include "config.h"
#include "timer.h"
#include <driver/timer.h>

/** Zdroje: 
 *  - https://github.com/pycom/pycom-esp-idf/blob/master/examples/peripherals/timer_group/main/timer_group_example_main.c
 *  - https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/timer.html
*/

#define TIMER_DIVIDER         80                                // Dělička časovače
#define TIMER_SCALE           (TIMER_BASE_CLK / TIMER_DIVIDER)  // Počet tiků za sekundu

hw_timer_t *timer = NULL;
volatile bool tickFlag = false;

// Obsluha přerušení časovače
void IRAM_ATTR onTimer() {
    tickFlag = true;
}

void setupTimer() {
    // Inicializace časovače
    timer = timerBegin(0, TIMER_DIVIDER, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, buzzerInterval * TIMER_SCALE / 1000, true);
    timerAlarmEnable(timer);
}

void updateTimerInterval() {
    timerAlarmWrite(timer, buzzerInterval * TIMER_SCALE / 1000, true); // Aktualizace intervalu
}