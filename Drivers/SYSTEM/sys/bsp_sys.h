#ifndef BSP_SYS_H
#define BSP_SYS_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "stm32h7xx.h"
#include "core_cm7.h"
#include "stm32h7xx_hal.h"



void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset);                       
void sys_cache_enable(void);                                                              
uint8_t sys_stm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq); 





#ifdef __cplusplus
}
#endif

#endif // BSP_SYS_H