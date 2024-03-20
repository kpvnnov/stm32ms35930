
#include "main.h"

#include <errno.h>
#include <sys/unistd.h> // STDOUT_FILENO, STDERR_FILENO
#include <stdio.h>


#define LED_PIN                                GPIO_PIN_13
#define LED_GPIO_PORT                          GPIOC
#define LED_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOC_CLK_ENABLE()
#define COM_PORT_DEBUG 

#ifdef COM_PORT_DEBUG
UART_HandleTypeDef UartHandle;


#endif
//static void SystemClock_Config(void);
static void Error_Handler(void);

__IO uint8_t ubButtonPress = 0;



int main(void)
{
  int x=0;
  #ifdef COM_PORT_DEBUG
  //int one_char='1';
  #endif
  HAL_Init();
  

  
  LED_GPIO_CLK_ENABLE();
  
  GPIO_InitTypeDef GPIO_InitStruct;
  
  GPIO_InitStruct.Pin = LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct); 


  /* Configure the system clock to 180 MHz */
  //SystemClock_Config();
 

  #ifdef COM_PORT_DEBUG
  UartHandle.Instance          = USARTx;
  
  UartHandle.Init.BaudRate     = 115200;
  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits     = UART_STOPBITS_1;
  UartHandle.Init.Parity       = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode         = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  #endif
HAL_Delay(1000);
    printf("How do you like this, Elon Musk? \n\r");

  while (1)
  {
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
    #ifdef COM_PORT_DEBUG
    //HAL_UART_Transmit(&UartHandle, (uint8_t *)&one_char, 1, 0xFFFF); 
    #endif
    HAL_Delay(500);
    //printf("Whoa cool:%d\n\r",x++);
    printf("Whoa cool:%d \n\r",x++);
    //HAL_UART_Transmit(&UartHandle, (uint8_t *)&one_char, 1, 0xFFFF); 
    //printf("sec cool:%d ",x++);
    //HAL_UART_Transmit(&UartHandle, (uint8_t *)&one_char, 1, 0xFFFF); 
    //printf("third cool:%d ",x++);
    HAL_Delay(500);
  }
}

#ifdef SWO_DEBUG
//overwrite printf() output to send via ITM (SWO)
int _write(int file, char *data, int len)
{
  if ((file != STDOUT_FILENO) && (file != STDERR_FILENO))
  {
    errno = EBADF;
    return -1;
  }

  for (int i = 0; i < len; i++)
  {
    ITM_SendChar(data[i]);
  }

  // return # of bytes written - as best we can tell
  return len;
}
#elif defined(COM_PORT_DEBUG)

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
//PUTCHAR_PROTOTYPE
//{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
//  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF); 

//  return ch;
//}

int _write(int file, char *data, int len) {
  if ((file != STDOUT_FILENO) && (file != STDERR_FILENO)) {
      errno = EBADF;
      return -1;
  }
  HAL_UART_Transmit(&UartHandle, (uint8_t *)data, (uint16_t) len, 0xFFFF); 
  return len;
}



#endif

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  //BSP_LED_On(LED2);
  //HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN,GPIO_PIN_SET);
  //HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN,GPIO_PIN_RESET);
  while(1)
  {
    HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
    HAL_Delay(250);
  }
}


/******************************************************************************/
/*   IRQ HANDLER TREATMENT Functions                                          */
/******************************************************************************/
/**
  * @brief  Function to manage Button push
  * @param  None
  * @retval None
  */
void UserButton_Callback(void)
{
  /* Update button press variable : to be checked in waiting loop in main program */
  ubButtonPress = 1;
}

