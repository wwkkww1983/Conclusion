/**
  ********************************  STM32F10x  *********************************
  *********************************  uC/OS-II  *********************************
  * @�ļ���     �� app_task.h
  * @����       �� strongerHuang
  * @��汾     �� V3.5.0
  * @ϵͳ�汾   �� V2.92
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2016��06��28��
  * @ժҪ       �� Ӧ�ó��������ͷ�ļ�
  ******************************************************************************/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef _APP_TASK_H
#define _APP_TASK_H

/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "ucos_ii.h"


/* �������� ------------------------------------------------------------------*/
void LedTask(void *p_arg);
void ComTask(void *p_arg);
#endif /* _APP_TASK_H */

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/