/* 
 * File:   delayCpuClocks.h
 * Author: Alcides Augusto Bezerra Neto
 *
 * Created on 19 de Novembro de 2025
 */

#ifndef DELAYCPUCLOCKS_H
#define	DELAYCPUCLOCKS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

    static inline void delayCpuClocks(uint32_t qtd) {
        uint32_t CP0_qtd = qtd / 2;
        uint32_t target = _CP0_GET_COUNT() + CP0_qtd;
        while (_CP0_GET_COUNT() < target);
    }

    static inline void delayCpuClocks1ms() {
        delayCpuClocks(80000); //80k
    }

    static inline void delayCpuClocks1s() {
        delayCpuClocks(80000000); //80M
    }

    static inline void delayCpuClocks500ms() {
        delayCpuClocks(40000000); //0.5 * 80e6
    }

    static inline void delayCpuClocksXms(uint32_t qtd) {
        delayCpuClocks(qtd * 80000); //qtd * 80e3
    }


#ifdef	__cplusplus
}
#endif

#endif	/* DELAYCPUCLOCKS_H */

