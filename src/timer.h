#ifndef TIMER_H
#define TIMER_H


// Nastavení časovače
void setupTimer();

// Aktualizace intervalu časovače
void updateTimerInterval();

// Příznak tiknutí časovače
extern volatile bool tickFlag;


#endif // TIMER_H