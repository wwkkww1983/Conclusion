#include <stdio.h>
#include<stdlib.h>
#include "stm32f10x.h"
#include "usart.h"

/*********************************************************************************************************
** Functoin name:       Time_Configuration
** Descriptions:        ��ʼ��TIM1
                        ���� ʱ�ӡ�TIM1������ʽ����
** input paraments:     ��
** output paraments:    ��    
** Returned values:     ��
*********************************************************************************************************/
void InitializeTimer(int n,float time)
{   
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TypeDef* TIMx;
	
	switch(++n)
	{  case 1: TIMx = TIM1; RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE); break;
	   case 2: TIMx = TIM2;	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	break;
	   case 3: TIMx = TIM3;	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	break;
	   case 4: TIMx = TIM4;	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	break;        
	   case 5: TIMx = TIM5;	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	break;
	}
   	TIM_DeInit(TIMx);                    					          // ��λTIM5��ʱ�� 
	TIM_TimeBaseStructure.TIM_Period = (int)(2000 * time);            // ÿT5�����һ���ӳ��� T5<30
	TIM_TimeBaseStructure.TIM_Prescaler = (36000-1);                  // ��Ƶ36000       
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;           // ʱ�ӷ�Ƶ  
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;       // �����������ϼ���
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                  // �ظ�����  
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

	TIM_ClearFlag(TIMx, TIM_FLAG_Update); 
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);                      //ʹ��TIM2�ж�Դ 
	TIM_Cmd(TIMx, DISABLE); 
}
/*********************************************************************************************************
** Functoin name:       TimeOn/Off Timx
** Descriptions:        �򿪻�ر�TIMx
                        
** input paraments:     ��
** output paraments:    ��    
** Returned values:     ��
*********************************************************************************************************/
void TurnOnTim(int x)
{
   int i = x + 1;
   switch(i)
   {
      case 1:	TIM_Cmd(TIM1, ENABLE);break;     //TIM1 ����
	  case 2:	TIM_Cmd(TIM2, ENABLE);break;     //TIM2 ����
	  case 3:	TIM_Cmd(TIM3, ENABLE);break;     //TIM3 ����
	  case 4:	TIM_Cmd(TIM4, ENABLE);break;     //TIM4 ����
	  case 5:	TIM_Cmd(TIM5, ENABLE);break;     //TIM5 ����
   } 
}
void TurnOffTim(int x)
{
  int i = x + 1;
  switch(i)
   {
      case 1:	TIM_Cmd(TIM1, DISABLE);break;   //TIM1 �ر�
	  case 2:	TIM_Cmd(TIM2, DISABLE);break;     //TIM2 �ر�
	  case 3:	TIM_Cmd(TIM3, DISABLE);break;     //TIM3 �ر�
	  case 4:	TIM_Cmd(TIM4, DISABLE);break;     //TIM4 �ر�
	  case 5:	TIM_Cmd(TIM5, DISABLE);break;     //TIM5 �ر�
   } 
}

///*********************************************************************************************************
//** Functoin name:       Timx�ж��˳�����
//** Descriptions:        ���жϱ�־λ�������ٴν����ж�
//                        
//** input paraments:     x Ҫ�˳������̺߳�
//** output paraments:    ��    
//** Returned values:     ��
//*********************************************************************************************************/
//void SubRoutineExit(int x)
//{ 
//   int i = x + 1; 
//   switch(i)
//   {
//      case 1:	TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update);break;     //TIM1 ���ж�
//	  case 2:	TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);break;     //TIM2 ���ж�
//	  case 3:	TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);break;     //TIM3 ���ж�
//	  case 4:	TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);break;     //TIM4 ���ж�
//	  case 5:	TIM_ClearITPendingBit(TIM5, TIM_FLAG_Update);break;     //TIM5 ���ж�
//   } 
//}
///*********************************************************************************************************
//** Functoin name:       Timx�ж���ں���
//** Descriptions:        �ж��жϱ�־λ�Ƿ�����ж�
//                        
//** input paraments:     x Ҫ��������̺߳� 
//** output paraments:    ��    
//** Returned values:     ����ɹ��������̣߳��򷵻�1�����򷵻�0
//*********************************************************************************************************/
//int SubRoutineEntry(int x)
//{ 
//   int i = x + 1; 
//   switch(i)
//   {
//      case 1:	if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  return 1;   //TIM1 �ж����
//	  case 2:	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  return 1;   //TIM2 �ж����
//	  case 3:	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  return 1;   //TIM3 �ж����
//	  case 4:	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  return 1;   //TIM4 �ж����
//	  case 5:	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  return 1;   //TIM5 �ж����
//   }  
//   return 0;
//}
//




