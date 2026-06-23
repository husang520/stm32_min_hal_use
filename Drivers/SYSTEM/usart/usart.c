#include "usart.h"



UART_HandleTypeDef g_uart1_handle;          /* UART句柄 */

/**
 * * 需要重定向 _write 函数 因为是 gnu 编译的 如果是 keil 则需要重定向 printf
 */

int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&g_uart1_handle,
                      (uint8_t *)ptr,
                      len,
                      HAL_MAX_DELAY);
    return len;
}

/**
 * @brief       串口X初始化函数
 * @param       baudrate: 波特率, 根据自己需要设置波特率值
 * @note        注意: 必须设置正确的时钟源, 否则串口波特率就会设置异常.
 *              这里的USART的时钟源在sys_stm32_clock_init()函数中已经设置过了.
 * @retval      无
 */
void usart_init(uint32_t baudrate)
{

    g_uart1_handle.Instance = USART_UX;                    /* USART1 */
    g_uart1_handle.Init.BaudRate = baudrate;               /* 波特率 */
    g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;   /* 字长为8位数据格式 */
    g_uart1_handle.Init.StopBits = UART_STOPBITS_1;        /* 一个停止位 */
    g_uart1_handle.Init.Parity = UART_PARITY_NONE;         /* 无奇偶校验位 */
    g_uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;   /* 无硬件流控 */
    g_uart1_handle.Init.Mode = UART_MODE_TX_RX;            /* 收发模式 */
    HAL_UART_Init(&g_uart1_handle);                        /* HAL_UART_Init()会使能UART1 */

}


/**
 * @brief       UART底层初始化函数
 * @param       huart: UART句柄类型指针
 * @note        此函数会被HAL_UART_Init()调用
 *              完成时钟使能，引脚配置，中断配置
 * @retval      无
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct;
    if (huart->Instance == USART_UX)                                /* 如果是串口1，进行串口1 MSP初始化 */
    {
        USART_UX_CLK_ENABLE();                                      /* USART1 时钟使能 */
        USART_TX_GPIO_CLK_ENABLE();                                 /* 发送引脚时钟使能 */
        USART_RX_GPIO_CLK_ENABLE();                                 /* 接收引脚时钟使能 */

        gpio_init_struct.Pin = USART_TX_GPIO_PIN;                   /* TX引脚 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                    /* 复用推挽 */
        gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
        gpio_init_struct.Alternate = USART_TX_GPIO_AF;              /* 复用为USART1 */
        HAL_GPIO_Init(USART_TX_GPIO_PORT, &gpio_init_struct);       /* 初始化发送引脚 */

        gpio_init_struct.Pin = USART_RX_GPIO_PIN;                   /* RX引脚 */
        gpio_init_struct.Alternate = USART_RX_GPIO_AF;              /* 复用为USART1 */
        HAL_GPIO_Init(USART_RX_GPIO_PORT, &gpio_init_struct);       /* 初始化接收引脚 */

#if USART_EN_RX
        HAL_NVIC_EnableIRQ(USART_UX_IRQn);                          /* 使能USART1中断通道 */
        HAL_NVIC_SetPriority(USART_UX_IRQn, 3, 3);                  /* 抢占优先级3，子优先级3 */
#endif
    }
}
