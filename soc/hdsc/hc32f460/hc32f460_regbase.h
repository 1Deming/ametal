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
 * \brief HC32F460 оƬ����Ĵ�����ַ����
 *
 * \internal
 * \par Modification history
 * - 1.00 19-12-23  cds, first implementation
 * \endinternal
 */

#ifndef __HC32F460_REGBASE_H
#define __HC32F460_REGBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup hc32f460_if_regbase
 * \copydoc hc32f460_regbase.h
 * @{
 */

#define HC32F460_SYSC_BASE          (0x40054000UL)  /** \brief SYSC����ַ */
#define HC32F460_MSTP_BASE          (0x40048000UL)  /** \brief MSTP����ַ */
#define HC32F460_GPIO_BASE          (0x40053800UL)  /** \brief GPIO����ַ */
#define HC32F460_EFM_BASE           (0x40010400UL)  /** \brief Ƕ��ʽFLASH��EFM������ַ */
#define HC32F460_INTC_BASE          (0x40051000UL)  /** \brief INTC����ַ */
#define HC32F460_UART1_BASE         (0x4001D000UL)  /** \brief UART1����ַ */
#define HC32F460_UART2_BASE         (0x4001D400UL)  /** \brief UART2����ַ */
#define HC32F460_UART3_BASE         (0x40021000UL)  /** \brief UART3����ַ */
#define HC32F460_UART4_BASE         (0x40021400UL)  /** \brief UART4����ַ */
#define HC32F460_EVENT_PORT_BASE    (0x40010800UL)  /** \brief EVENT_PORT����ַ */
#define HC32F460_SYSTICK_BASE       (0xE000E010UL)  /** \brief SYSTICK����ַ */
#define HC32F460_DMA1_BASE          (0x40053000UL)  /** \brief DMA1����ַ */
#define HC32F460_DMA2_BASE          (0x40053400UL)  /** \brief DMA2����ַ */
#define HC32F460_AOS_BASE           (0x40010800UL)  /** \brief AOS����ַ */
#define HC32F460_TIMER0_1_BASE      (0x40024000UL)  /** \brief TIMER01����ַ */
#define HC32F460_TIMER0_2_BASE      (0x40024400UL)  /** \brief TIMER02����ַ */
#define HC32F460_TMRA1_BASE         (0x40015000UL)  /** \brief TIMERA01����ַ */
#define HC32F460_TMRA2_BASE         (0x40015400UL)  /** \brief TIMERA02����ַ */
#define HC32F460_TMRA3_BASE         (0x40015800UL)  /** \brief TIMERA03����ַ */
#define HC32F460_TMRA4_BASE         (0x40015C00UL)  /** \brief TIMERA04����ַ */
#define HC32F460_TMRA5_BASE         (0x40016000UL)  /** \brief TIMERA05����ַ */
#define HC32F460_TMRA6_BASE         (0x40016400UL)  /** \brief TIMERA06����ַ */
#define HC32F460_TMR41_BASE         (0x40017000UL)  /** \brief TIMER401����ַ */
#define HC32F460_TMR42_BASE         (0x40024800UL)  /** \brief TIMER402����ַ */
#define HC32F460_TMR43_BASE         (0x40024C00UL)  /** \brief TIMER403����ַ */
#define HC32F460_TMR4_CR            (0x40055408UL)  /** \brief TIMER4_CR����ַ */
#define HC32F460_TMR61_BASE         (0x40018000UL)  /** \brief TIMER601����ַ */
#define HC32F460_TMR62_BASE         (0x40018400UL)  /** \brief TIMER602����ַ */
#define HC32F460_TMR63_BASE         (0x40018800UL)  /** \brief TIMER603����ַ */
#define HC32F460_TMR6_CR            (0x40018000UL)  /** \brief TIMER6_CR����ַ */
#define HC32F460_I2C1_BASE          (0x4004E000UL)  /** \brief I2C1����ַ */
#define HC32F460_I2C2_BASE          (0x4004E400UL)  /** \brief I2C2����ַ */
#define HC32F460_I2C3_BASE          (0x4004E800UL)  /** \brief I2C3����ַ */
#define HC32F460_RTC_BASE           (0x4004C000UL)  /** \brief RTC����ַ */
#define HC32F460_CAN_BASE           (0x40070400UL)  /** \brief CAN����ַ */
#define HC32F460_QSPI_BASE          (0x9C000000UL)  /** \brief QSPI����ַ */

/**
 * \name �����ڴ�ӳ���ַ����
 * @{
 */


/** @} */

/**
 * @} hc32f460_if_regbase
 */

#ifdef __cplusplus
}
#endif

#endif/* __HC32F460_REGBASE_H */

/* end of file */