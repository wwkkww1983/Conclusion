/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

frame frm=
{
    0x00,
    0x00,
    0x00,
    0x00,
    0x00   
};
disframe disfrm=
{
    0x00,
    0x00,
    0x00
};

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */

void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
   
}
/*��ʱ��1�жϴ���*/
//void TIM5_IRQHandler(void)
//{
////    u8 i;
//	
//   if (TIM_GetITStatus(TIM5, TIM_IT_Update) == SET)
//   {
//	  TIM_ClearITPendingBit(TIM5,TIM_FLAG_Update);  
//	  
//	  co2flag =1;	
//   }
//  
//}

/*��ʱ��2�жϴ���*/

void TIM2_IRQHandler(void)
{
   u8 j=0;
   colcnt++;
   if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
   {
          TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 
	  }
//	   IC2Value = TIM_GetCapture2(TIM2); 
//	   IC1Value = TIM_GetCapture1(TIM2) ;                        //��ȡIC2����Ĵ�����ֵ����ΪPWM���ڵļ���ֵ
       
	else if (TIM_GetITStatus(TIM2,TIM_IT_CC2) == SET)
      {
                                               //����PWMƵ�ʡ�
		 // if(Capflag==0)
		 //  { 
		    IC2Value = TIM_GetCapture2(TIM2);
		 //    Capflag=1;
		 //  } 
         //  else if(Capflag==1)
	   	 //  {  
		   IC1Value = TIM_GetCapture1(TIM2) ;                        //��ȡIC2����Ĵ�����ֵ����ΪPWM���ڵļ���ֵ
		 //  	  Capflag=0;
		 //  }
     	 
		 DutyCycle = 2000*(IC1Value)/(IC2Value)  ;   
	      if(DutyCycle!=0)
	      CO2sum[99] = DutyCycle;

	      for(j=0;j<99;j++)
          {
	  	    CO2sum[j] =  CO2sum[j+1];
	      }
		 TIM_ClearITPendingBit(TIM2, TIM_IT_CC2); 

	  }


	  Tim2SP() ;


	 
}




/*��ʱ��3�жϴ�������Ҫ�������ڽ�������*/
void TIM3_IRQHandler(void)
{     

   if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
   {
      TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);      
      getdataflag=1;
   }
  
}

/*��ʱ��4�жϴ�������Ҫ�������ڽ�������*/
void TIM4_IRQHandler(void)
{     

   if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
   {
      TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update);      
	  dataProcess();
   }
  
}
/*����1�жϴ���*/
void USART1_IRQHandler(void)
{
 
//    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
//    {
//        USART_ClearFlag(USART1,USART_FLAG_ORE); //��SR��ʵ���������־
//        USART_ReceiveData(USART1);        
//    }
//    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
//    {
//        usart1_buff[frm.num]=USART_ReceiveData(USART1);
//        usart1_buff[frm.num]-=0x33;
//        frm.num++;
////        if(frm.num==1)
////        {
////            TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);             
////        }
//        USART_ClearITPendingBit(USART1,USART_IT_RXNE);        
//    }  
//	usart2_senddata(Send_read);
}

/*����1��������*/
void usart_senddata(u8 arr[])
{

}

void USART2_IRQHandler(void)
{
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
	 USART_ClearITPendingBit(USART2,USART_IT_RXNE);

	 usart2_buff[num]=USART_ReceiveData(USART2);
        
		num++;

	 if (num>=2)
	{
		 if((usart2_buff[0]==0x55)&&(usart2_buff[1]==0x66))
		{      
			switch(num)
			{
				case 1:break;
				case 24:
				if((usart2_buff[23]==0x55)&&(usart2_buff[22]==0x66))
				{Receiver_process();
				num=0;
				kflag0=0;}
				else{num=0;}break;
				default:break;
			}
		}
		else
		{
			num=0;
		}
	}
  }
  		Usart2_Rx()	 ;

		USART_ITConfig(USART2,USART_IT_TXE,DISABLE);			  	//������� �ر��ж�

}


void usart2_senddata(u8 typeA)
{
    u8 i;
   
  Usart2_Tx() ;
  delay_ms(1);
	switch(typeA)
 	{
		case 0:
		for(i=0;i<24;i++)
		{
		  USART_SendData(USART2,Send_read[i]); //read  
		  delay_ms(2);
		 }
		break;
		
		case 1:
		for(i=0;i<24;i++)
		{
		USART_SendData(USART2,Send_set[i]); //set
		 delay_ms(2);
		return_flag=1;
		}
		break;
		
		case 2:
		for(i=0;i<24;i++)
		{USART_SendData(USART2,Send_start[i]);//start
		 delay_ms(2);
		return_flag=2;
		}
		break;
	
		case 3:
		for(i=0;i<24;i++)
		{USART_SendData(USART2,Send_stop[i]);//stop
		 delay_ms(2);
		return_flag=3;	 }
		break;
	
		default:
		break;
	}

	USART_ITConfig(USART2,USART_IT_TXE,DISABLE);
	Usart2_Rx()	 ;

}


u8 CRC_check(u8 arr[],u8 start, u8 stop)

{
    u8 i,value;
    u16 tep=0;
 
    for(i=start;i<stop;i++)
    {
        tep+=arr[i];
    }
    value= tep%100;
    return value;
}


void packagedata(u16 PvRH,u16 PvTe,u16 SvTe,u16 PvCO2,u16 SvCO2)
{
	Send_read[3]=PvRH/100;
	Send_read[4]=PvRH%100;
	Send_read[5]=PvTe/100;
	Send_read[6]=PvTe%100;
	Send_read[7]=SvTe/100;
	Send_read[8]=SvTe%100;
	Send_read[9]=PvCO2/100;
	Send_read[10]=PvCO2%100;
	Send_read[11]=SvCO2/100;
	Send_read[12]=SvCO2%100;
	//Send_set[20]=unoccup;
	Send_read[21]=(Send_read[3]+Send_read[4]+Send_read[5]+Send_read[6]+Send_read[7]+Send_read[8]+Send_read[9]+Send_read[10]+Send_read[11]+Send_read[12]+Send_read[13]+Send_read[14]+12)%100;
}

void Receiver_process(void)
{
	switch(usart2_buff[2])
    {
     //   case 1:dataProcess(Mtemp, Mhum, usart2_buff[7]*100+usart2_buff[8]);showonoff(usart2_buff[9]);break;
		case 2:Send_finish(3);break;
		case 3:Send_finish(1);break;
		case 4:Send_finish(2);break;
        default: break;
     }
}	  
	  


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/