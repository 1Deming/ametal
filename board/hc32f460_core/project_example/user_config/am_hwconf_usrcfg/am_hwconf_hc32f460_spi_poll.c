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
 * \brief HC32F460 SPI �û������ļ�
 * \sa am_hwconf_hc32f460_spi_poll.c
 *
 * \internal
 * \par Modification history
 * - 1.00 20-03-24  cds, first implementation.
 * \endinternal
 */

#include "am_hc32f460.h"
#include "ametal.h"
#include "am_hc32f460_spi_poll.h"
#include "am_gpio.h"
#include "hw/amhw_hc32f460_spi.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32f460_spi_poll
 * \copydoc am_hwconf_hc32f460_spi_poll.c
 * @{
 */
/** \brief SPI3 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi3_poll_init (void)
{
    am_gpio_pin_cfg(PIOE_0,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_SCK));
    am_gpio_pin_cfg(PIOE_2,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_MOSI));
    am_gpio_pin_cfg(PIOE_3,  GPIO_AFIO(AMHW_HC32F460_AFIO_SPI3_MISO));

    am_clk_enable(CLK_SPI3);
}

/** \brief ���SPI3 ƽ̨��ʼ�� */
static void __hc32f460_plfm_spi3_poll_deinit (void)
{

    /* �ͷ�����Ϊ����ģʽ */
    am_gpio_pin_cfg(PIOE_0,  GPIO_AFIO(AM_GPIO_INPUT));
    am_gpio_pin_cfg(PIOE_2,  GPIO_AFIO(AM_GPIO_INPUT));
    am_gpio_pin_cfg(PIOE_3,  GPIO_AFIO(AM_GPIO_INPUT));

    am_clk_disable(CLK_SPI3);
}

/**
 * \brief SPI3 �豸��Ϣ
 */
const  struct am_hc32f460_spi_poll_devinfo  __g_spi3_poll_devinfo = {
    HC32F460_SPI3_BASE,                     /**< \brief SPI3�Ĵ���ָ�� */
    CLK_SPI3,                               /**< \brief ʱ��ID�� */
    __hc32f460_plfm_spi3_poll_init,         /**< \brief SPI0ƽ̨��ʼ������ */
    __hc32f460_plfm_spi3_poll_deinit        /**< \brief SPI0ƽ̨���ʼ������ */
};

/** \brief SPI3 �豸ʵ�� */
static am_hc32f460_spi_poll_dev_t __g_spi3_poll_dev;

/** \brief SPI0 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_hc32f460_spi3_poll_inst_init (void)
{
    return am_hc32f460_spi_poll_init(&__g_spi3_poll_dev, &__g_spi3_poll_devinfo);
}

/** \brief SPI3 ʵ�����ʼ�� */
void am_hc32f460_spi3_poll_inst_deinit (am_spi_handle_t handle)
{
    am_hc32f460_spi_poll_deinit(handle);
}
#if 0
/** \brief SPI1 ƽ̨��ʼ�� */
static void __zlg118_plfm_spi1_poll_init (void)
{
    am_gpio_pin_cfg(PIOB_10, PIOB_10_SPI1_SCK  | PIOB_10_OUT_PP);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI1_MOSI | PIOB_15_OUT_PP);
    am_gpio_pin_cfg(PIOC_2,  PIOC_2_SPI1_MISO  | PIOC_2_INPUT_PU);

    am_clk_enable(CLK_SPI1);
}

/** \brief ���SPI1 ƽ̨��ʼ�� */
static void __zlg118_plfm_spi1_poll_deinit (void)
{

    /* �ͷ�����Ϊ����ģʽ */
    am_gpio_pin_cfg(PIOB_10, PIOB_10_INPUT_PU);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_INPUT_PU);
    am_gpio_pin_cfg(PIOC_2,  PIOC_2_INPUT_PU);

    am_clk_disable(CLK_SPI1);
}

/**
 * \brief SPI1 �豸��Ϣ
 */
const  struct am_zlg118_spi_poll_devinfo  __g_spi1_poll_devinfo = {
    ZLG118_SPI1_BASE,                       /**< \brief SPI1�Ĵ���ָ�� */
    CLK_SPI1,                               /**< \brief ʱ��ID�� */
    __zlg118_plfm_spi1_poll_init,           /**< \brief SPI1ƽ̨��ʼ������ */
    __zlg118_plfm_spi1_poll_deinit          /**< \brief SPI1ƽ̨���ʼ������ */
};

/** \brief SPI1 �豸ʵ�� */
static am_zlg118_spi_poll_dev_t __g_spi1_poll_dev;

/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_zlg118_spi1_poll_inst_init (void)
{
    return am_zlg118_spi_poll_init(&__g_spi1_poll_dev, &__g_spi1_poll_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_zlg118_spi1_poll_inst_deinit (am_spi_handle_t handle)
{
    am_zlg118_spi_poll_deinit(handle);
}
#endif
/**
 * @}
 */

/* end of file */
