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
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �� J14 �� KEY �� PIOA_8 �̽���һ��
 *
 * - ʵ������
 *   1. ��һ�ΰ��� LED0 ��Ϩ���ٰ�һ�ΰ��� LED0 ��������˷�����
 *
 * \note
 *    LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOB_1 ���ơ�
 *
 * \par Դ����
 * \snippet demo_am159_core_hw_gpio.c src_am159_core_hw_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-15  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am159_core_hw_gpio
 * \copydoc demo_am159_core_hw_gpio.c
 */

/** [src_am159_core_hw_gpio] */
#include <hc32f460_pin.h>
#include <hw/amhw_hc32f460_gpio.h>
#include "ametal.h"
#include "am_clk.h"
#include "am_vdebug.h"
//#include "am_zmf159.h"
//#include "demo_zlg_entries.h"
//#include "demo_zmf159_core_entries.h"
#include "hc32f460_regbase.h"


#define INPUT_PIN  PIOC_13 /**< \brief �������� */
#define OUTPUT_PIN PIOE_6  /**< \brief ������� */

/**
 * \brief �������
 */
void demo_hc32f460_core_hw_gpio_entry (void)
{
    AM_DBG_INFO("demo zmf159_core hw gpio!\r\n");

    /* ʹ��ʱ�� */
//    am_clk_enable(CLK_IOPA);
//    am_clk_enable(CLK_SYSCFG);

    demo_zlg_hw_gpio_entry((amhw_hc32f460_gpio_t*)HC32F460_GPIO_BASE, INPUT_PIN, OUTPUT_PIN);
}
/** [src_am159_core_hw_gpio] */

/* end of file */
