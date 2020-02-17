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
 * \brief HC32F460 ģ�幤��
 *
 * - ʵ������:
 *   ģ������:����3��ӡ��ʱ��Ƶ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-01-10  cds, first implementation
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
#include "hc32f460_clk.h"
#include "am_clk.h"

extern void uart_init(void);
extern void clk_printf(char *str, am_clk_id_t clk_id);

int am_main (void)
{

    uart_init();
    clk_printf("SYSCLK", CLK_SYSCLK_DIV1);
    clk_printf("CLK_XTAL", CLK_XTAL);
    clk_printf("CLK_MPLL", CLK_MPLL);
    clk_printf("CLK_MPLLP", CLK_MPLLP);
    clk_printf("CLK_MPLLQ", CLK_MPLLQ);
    clk_printf("CLK_MPLLR", CLK_MPLLR);
    clk_printf("CLK_HCLK", CLK_HCLK);
    clk_printf("CLK_PCLK0", CLK_PCLK0);
    clk_printf("CLK_PCLK1", CLK_PCLK1);
    clk_printf("CLK_PCLK2", CLK_PCLK2);
    clk_printf("CLK_PCLK3", CLK_PCLK3);
    clk_printf("CLK_PCLK4", CLK_PCLK4);

    while (1) {

    }
}

/* end of file */
