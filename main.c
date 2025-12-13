// PIC32MX795F512L Configuration Bit Settings

// 'C' source line config statements

// DEVCFG3
#pragma config USERID = 0xFFFF          // Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config FSRSSEL = PRIORITY_7     // SRS Select (SRS Priority 7)
#pragma config FMIIEN = ON              // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config FCANIO = ON              // CAN I/O Pin Select (Default CAN I/O)
#pragma config FUSBIDIO = ON            // USB USID Selection (Controlled by the USB Module)
#pragma config FVBUSONIO = ON           // USB VBUS ON Selection (Controlled by USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
#pragma config UPLLIDIV = DIV_12        // USB PLL Input Divider (12x Divider)
#pragma config UPLLEN = OFF             // USB PLL Enable (Disabled and Bypassed)
#pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider (PLL Divide by 1)

// DEVCFG1
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Primary Osc w/PLL (XT+,HS+,EC+PLL))
#pragma config FSOSCEN = ON             // Secondary Oscillator Enable (Enabled)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = XT             // Primary Oscillator Configuration (XT osc mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/1)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include "delayCpuClocks.h"
#include "GPIOPinSetting.h"

void setupRegs() {
    INTCONbits.MVEC = 1; // habilita modo multi-vetor
    __builtin_enable_interrupts(); // habilita interrupções globais

    //  Timer 2
    T2CON = 0; // desabilitar o clock (por garantia)
    T2CONbits.TCS = 0; // clock do barramento (40 MHz)
    T2CONbits.TCKPS = 7; // int 7 => prescale = 1:256 => f2 = 40 MHz / 256 = 156256
    PR2 = 0xFFFF; // 0.419 segundos
    TMR2 = 0; // zerar o cronômetro 2

    //  Interrupção do timer 2
    IFS0bits.T2IF = 0; // Clear flag
    IEC0bits.T2IE = 1; // habilitar a interrupção
    IPC2bits.T2IP = 4; // prioridade 4 (prioridade média)

    //  Buttons
    TRISEbits.TRISE1 = INPUT; // configurar RE1 como entrada (digital? SIM)

    //  LED da placa PIC100-A
    TRISEbits.TRISE0 = OUTPUT; // configura RE0 como saída
    LATEbits.LATE0 = LOW; // começa desligado
}

void __attribute__((interrupt(IPL4AUTO), vector(_TIMER_2_VECTOR))) T2ISR(void) {
    IFS0bits.T2IF = 0; // Limpa flag
    LATEbits.LATE0 ^= 1; // Alterna o LED
}

int main(void) {
    setupRegs();

    T2CONbits.ON = 1; // ligar o timer 2


    while (1) {

    }
}
