#include "stm32f10x.h"
#include "usart.h"	
#include "usart3.h"
#include "delay.h"
#include "sys.h"
#include "led.h"

int main()
{
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	usart3_init(9600);
	while(1){}
   
}

void USART3_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收到数据
	{	 
		res =USART_ReceiveData(USART3);
		USART_SendData(USART1, res);
    u3_printf("%d",res);
		
	}  				 											 
}   
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		    Res =USART_ReceiveData(USART1);	//读取接收到的数据
		    USART_SendData(USART3, Res);	
         			
     } 
}
