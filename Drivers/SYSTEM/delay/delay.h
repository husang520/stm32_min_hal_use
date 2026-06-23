#ifndef DELAY_H
#define DELAY_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "bsp_sys.h"


void delay_init(uint16_t sysclk); /* 初始化延迟函数 */
void delay_ms(uint16_t nms);      /* 延时nms */
void delay_us(uint32_t nus);      /* 延时nus */



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // DELAY_H