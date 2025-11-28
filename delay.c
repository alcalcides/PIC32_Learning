
#include <xc.h>
#include "delay.h"

static uint32_t core_clock_hz = 0;   // Guarda o clock real
static uint32_t ticks_per_us = 0;
static uint32_t ticks_per_ms = 0;

// ------------------------------------------------------------
// Detecta automaticamente o clock real do CPU
// ------------------------------------------------------------
void delayInit(void)
{
    uint32_t pll_input_div  = (DEVCFG2bits.FPLLIDIV & 0x7) + 1;      // 1?10
    uint32_t pll_multiplier = (DEVCFG2bits.FPLLMUL  & 0x7) * 5 + 15; // 15?24
    uint32_t pll_output_div = 1 << (DEVCFG2bits.FPLLODIV & 0x3);     // 1,2,4,8,16,32
    
    uint32_t posc = 4000000UL;   // 4 MHz (coloque o valor do seu cristal)

    // SYSCLK = (POSC / FPLLIDIV) * FPLLMUL / FPLLODIV
    uint32_t sysclk = (posc / pll_input_div) * pll_multiplier / pll_output_div;

    // Core Timer = SYSCLK / 2
    core_clock_hz = sysclk / 2;

    ticks_per_us = core_clock_hz / 1000000UL;
    ticks_per_ms = core_clock_hz / 1000UL;
}

// ------------------------------------------------------------
// Espera um número exato de ticks do Core Timer
// ------------------------------------------------------------
void waitTicks(uint32_t ticks)
{
    uint32_t start = _CP0_GET_COUNT();
    while ((_CP0_GET_COUNT() - start) < ticks);
}

// ------------------------------------------------------------
// Delay em microssegundos
// ------------------------------------------------------------
void delay_us(uint32_t us)
{
    waitTicks(us * ticks_per_us);
}

// ------------------------------------------------------------
// Delay em milissegundos
// ------------------------------------------------------------
void delay_ms(uint32_t ms)
{
    while (ms--)
        waitTicks(ticks_per_ms);
}

// ------------------------------------------------------------
// Delay em segundos
// ------------------------------------------------------------
void delay_s(uint32_t s)
{
    while (s--)
        waitTicks(core_clock_hz);
}

uint32_t getCoreClockHz(void)
{
    return core_clock_hz;
}
