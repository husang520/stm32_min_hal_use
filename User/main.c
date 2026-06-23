
#include "bsp_sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"








int main(void){

    
    // * 这里做系统初始化
    HAL_Init();                                     // * hal 库初始化
    sys_stm32_clock_init(160, 5, 2, 4);             // * 系统时钟使能

    /****************************************************************/
    // * 这里做相关外设的初始化
    delay_init(400);                                // * 延时函数初始化
    usart_init(115200);                             // * 串口初始化
    led_init();                                     // * led 初始化

    /****************************************************************/



    while(1){
        printf("hello\r\n");
        LED1_TOGGLE();
        delay_ms(500);

    }

    return 0;
}




