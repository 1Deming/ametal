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
 * \brief MM32L373 bootloader��Ӧ�ó��򹤳�
 *
 * - �������裺
 *    �ο� {sdk}\ametal\documents\MM32L373 Ŀ¼�� mm32l373_core_kft_bootloader �����ֲᡣ
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-07  nwt, first implementation
 * \endinternal
 */

/**
 * \brief �������
 */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "demo_mm32l373_core_entries.h"
#include "mm32l373_pin.h"
#include "am_mm32l373_inst_init.h"

int am_main (void)
{
    AM_DBG_INFO("application : Start up successful!\r\n");

    demo_mm32l373_core_boot_kft_application_entry();

    while (1) {

    }
}

/* end of file */
