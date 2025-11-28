#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>
    
// Inicializa o módulo de delay (detecta automaticamente o clock da CPU)
void delayInit(void);

// Delay baseado no Core Timer
void waitTicks(uint32_t ticks);

// Delays de tempo real
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void delay_s(uint32_t s);

// Retorna a frequência do core (CPU clock)
uint32_t getCoreClockHz(void);

#endif
