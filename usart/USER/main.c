#include "stm32f10x.h"
#include "usart.h"	
#include "usart3.h"
#include "delay.h"
#include "sys.h"
#include "led.h"

int main()
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	usart3_init(9600);
	while(1){}
   
}

void USART3_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//���յ�����
	{	 
		res =USART_ReceiveData(USART3);
		USART_SendData(USART1, res);
    u3_printf("%d",res);
		
	}  				 											 
}   
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		    Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		    USART_SendData(USART3, Res);	
         			
     } 
}
