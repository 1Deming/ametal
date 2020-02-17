/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/
/**
 * \file
 * \brief MM32L073 bootloader �� bootloader ����
 *
 * - �������裺
 *    �ο� {sdk}\ametal\documents\mm32l073_coreĿ¼�� mm32l073 bootloader �����ֲᡣ
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-14  yrh, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_mm32l073_core_entries.h"
#include "am_mm32l073_inst_init.h"
/**
 * \brief AMetal Ӧ�ó������
 */
int am_main (void)
{
    demo_mm32l073_core_bootloader_entry();
    while(1) {

		}	

}
