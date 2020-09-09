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
 * \brief GPIOƽ̨�������ߺ�
 *
 * ���ļ��������� \sa stm32f103rbt6_pin.h. �䶨����GPIOƽ̨���ŵĸ������ܡ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-07-3  zc, first implementation
 * \endinternal
 */

#ifndef __AM_STM32F103RBT6_GPIO_UTIL_H
#define __AM_STM32F103RBT6_GPIO_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_stm32f103rbt6_if_gpio_util
 * \copydoc am_stm32f103rbt6_gpio_util.h
 * @{
 */

/**
 * \brief ƽ̨�궨��
 *
 * bit[31:12] ƽ̨����
 *
 */

/**
 * \name ����λ��
 * @{
 */
#define AM_STM32F103RBT6_GPIO_OUTRES_RATE                  AM_BIT(13)     /**< \brief �ܽ���Ӧ���� */
#define AM_STM32F103RBT6_GPIO_MODE                         AM_BIT(14)     /**< \brief �ܽ�ģʽ */
#define AM_STM32F103RBT6_GPIO_REMAP                        AM_BIT(15)     /**< \brief �ܽŸ��ù���ʹ�� */

#define AM_STM32F103RBT6_GPIO_OUTRESRATEBITS_START         18        /**< \brief �����Ӧ��������ʼλ */
#define AM_STM32F103RBT6_GPIO_OUTRESRATEBITS_LEN           2         /**< \brief �����Ӧ�����볤�� */

/** \brief ����Ӧ������ */
#define AM_STM32F103RBT6_GPIO_OUTRES_RATE_CODE(a)          (AM_SBF((a), AM_STM32F103RBT6_GPIO_OUTRESRATEBITS_START) |  \
                                                      AM_STM32F103RBT6_GPIO_OUTRES_RATE)

/** \brief ��ȡ��Ӧ������ */
#define AM_STM32F103RBT6_GPIO_OUTRES_RATE_GET(data)        AM_BITS_GET((data), AM_STM32F103RBT6_GPIO_OUTRESRATEBITS_START, \
                                                                          AM_STM32F103RBT6_GPIO_OUTRESRATEBITS_LEN)

#define AM_STM32F103RBT6_GPIO_MODEBITS_START               20        /**< \brief ģʽ����ʼλ */
#define AM_STM32F103RBT6_GPIO_MODEBITS_LEN                 4         /**< \brief ģʽ�볤�� */

/** \brief ��ģʽ�� */
#define AM_STM32F103RBT6_GPIO_MODE_CODE(a)                 (AM_SBF((a), AM_STM32F103RBT6_GPIO_MODEBITS_START) |  \
                                                      AM_STM32F103RBT6_GPIO_MODE)

/** \brief ��ȡģʽ�� */
#define AM_STM32F103RBT6_GPIO_MODE_GET(data)               AM_BITS_GET((data), AM_STM32F103RBT6_GPIO_MODEBITS_START, \
                                                                          AM_STM32F103RBT6_GPIO_MODEBITS_LEN)

#define AM_STM32F103RBT6_GPIO_REMAP_PERIPHERAL_START       24  /**< \brief ��ӳ����������ʼλ */
#define AM_STM32F103RBT6_GPIO_REMAP_PERIPHERAL_LEN         5   /**< \brief ��ӳ�������볤�� */

/** \brief ��ȡ��ӳ�������� */
#define AM_STM32F103RBT6_GPIO_REMAP_PERIPHERAL_GET(data)   AM_BITS_GET((data), AM_STM32F103RBT6_GPIO_REMAP_PERIPHERAL_START, \
                                                                          AM_STM32F103RBT6_GPIO_REMAP_PERIPHERAL_LEN)

#define AM_STM32F103RBT6_GPIO_REMAP_MODE_START             29  /**< \brief ��ӳ��ģʽ����ʼλ */
#define AM_STM32F103RBT6_GPIO_REMAP_MODE_LEN               2   /**< \brief ��ӳ��ģʽ�볤�� */

/** \brief ��ȡ��ӳ��ģʽ�� */
#define AM_STM32F103RBT6_GPIO_REMAP_MODE_GET(data)         AM_BITS_GET((data), AM_STM32F103RBT6_GPIO_REMAP_MODE_START, \
                                                                          AM_STM32F103RBT6_GPIO_REMAP_MODE_LEN)

/** \brief ��ȡ��ӳ��������  (PERIPHERAL,MODE) */
#define AM_STM32F103RBT6_GPIO_REMAP_CODE(a,b)              (AM_SBF((AM_SBF(b, AM_STM32F103RBT6_GPIO_REMAP_PERIPHERAL_LEN) | a), \
                                                                         AM_STM32F103RBT6_GPIO_REMAP_PERIPHERAL_START) |   \
                                                                         AM_STM32F103RBT6_GPIO_REMAP)
/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_STM32F103RBT6_GPIO_UTIL_H */

/* end of file */