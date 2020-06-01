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
 * \brief HC32F460ϵ�������������������̺����������
 * \sa    demo_hc32f460_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 17-05-02  tee, first implementation
 * \endinternal
 */

#ifndef __DEMO_HC32F460_ENTRIES_H
#define __DEMO_HC32F460_ENTRIES_H

#include "am_clk.h"
#include "am_timer.h"
#include "am_can.h"
#include "hw/amhw_hc32f460_gpio.h"
#include "hw/amhw_hc32f460_uart.h"
#include "hw/amhw_hc32f460_dma.h"
#include "am_hc32f460_dma.h"
#include "am_hc32f460_qspi.h"
#include "hw/amhw_hc32f460_spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ADC INT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc   ָ��ADC����Ĵ������ָ��
 * \param[in] int_num    �жϱ��
 * \param[in] chan       ADCͨ����
 * \param[in] vref_mv    �ο���ѹ
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_int_entry (void    *p_hw_adc,
                                     int      int_num,
                                     uint8_t  chan,
                                     uint32_t vref_mv);

/**
 * \brief ADC��ͨ��DMA�������̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] p_hw_adc   ָ�� ADC����Ĵ������ָ��
 * \param[in] p_adc_chan ADCͨ����������
 * \param[in] p_dma_dev  ָ�� DMA�豸��ָ��
 * \param[in] chan_num   ADCͨ����
 * \param[in] vref_mv    �ο���ѹ
 * \param[in] dma_chan   DMAͨ����
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_dma_entry (void                  *p_hw_adc,
                                     amhw_adc_chmux_t      *p_adc_chan,
                                     am_hc32f460_dma_dev_t *p_dma_dev,
                                     int                    chan_num,
                                     uint32_t               vref_mv,
                                     int                    dma_chan);


/**
 * \brief ADC ��ͨ��ת�� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc   ָ�� ADC����Ĵ������ָ��
 * \param[in] int_num    �жϱ��
 * \param[in] vref_mv    �ο���ѹ
 * \param[in] p_adc_chan ADCͨ����������
 * \param[in] chan_num   ADCͨ����
 *
 * \return ��
 */
void demo_hc32f460_hw_multichan_adc_entry (void    *p_hw_adc,
                                           int      int_num,
                                           uint32_t vref_mv,
                                           amhw_adc_chmux_t     *p_adc_chan,
                                           uint8_t  chan_num);

/**
 * \brief ADC ��ͨ������ת�� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc   ָ�� ADC����Ĵ������ָ��
 * \param[in] int_num    �жϱ��
 * \param[in] vref_mv    �ο���ѹ
 * \param[in] p_adc_chan ADCͨ����������
 * \param[in] chan_num   ADCͨ����
 *
 * \return ��
 */
void demo_hc32f460_hw_multichan_seq_adc_entry (void             *p_hw_adc,
                                               int               int_num,
                                               uint32_t          vref_mv,
                                               amhw_adc_chmux_t *p_adc_chan,
                                               uint8_t           chan_num);

/**
 * \brief ADC ����A�¼����� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc   ָ�� ADC����Ĵ������ָ��
 * \param[in] int_num    �жϱ��
 * \param[in] chan_num   ADCͨ����
 * \param[in] vref_mv    �ο���ѹ
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_seq_a_event_trigger_entry (void    *p_hw_adc,
                                                     int      int_num,
                                                     uint8_t  chan,
                                                     uint32_t vref_mv);

/**
 * \brief ADC ����A��B˫�����¼����� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc ָ�� ADC����Ĵ������ָ��
 * \param[in] int_num  �жϱ��
 * \param[in] chan_a   ADC����Aͨ����
 * \param[in] chan_b   ADC����Bͨ����
 * \param[in] vref_mv  �ο���ѹ
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_seq_a_b_event_trigger_entry (void    *p_hw_adc,
                                                       int      int_num,
                                                       uint8_t  chan_a,
                                                       uint8_t  chan_b,
                                                       uint32_t vref_mv);

/**
 * \brief ��ADC Эͬ���� ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc1    ָ�� ADC1����Ĵ������ָ��
 * \param[in] p_hw_adc2    ָ�� ADC2����Ĵ������ָ��
 * \param[in] int_num_adc1 ADC1�жϱ��
 * \param[in] int_num_adc2 ADC2�жϱ��
 * \param[in] chan_adc1    ADC1ͨ����
 * \param[in] chan_adc2    ADC2ͨ����
 * \param[in] vref_mv      �ο���ѹ
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_sync_entry (void    *p_hw_adc1,
                                      void    *p_hw_adc2,
                                      int      int_num_adc1,
                                      int      int_num_adc2,
                                      uint8_t  chan_adc1,
                                      uint8_t  chan_adc2,
                                      uint32_t vref_mv);

/**
 * \brief ADC PGA ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc  ָ�� ADC����Ĵ������ָ��
 * \param[in] int_num   ADC�жϱ��
 * \param[in] chan      ADCͨ����
 * \param[in] vref_mv   �ο���ѹ
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_pga_entry (void    *p_hw_adc,
                                     int      int_num,
                                     uint8_t  chan,
                                     uint32_t vref_mv);

/**
 * \brief ADC PGA ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_adc  ָ�� ADC����Ĵ������ָ��
 * \param[in] int_num   EOC�жϱ��
 * \param[in] chan      SEQCMP�жϱ��
 * \param[in] chan      ADCͨ����
 * \param[in] vref_mv   �ο���ѹ
 *
 * \return ��
 */
void demo_hc32f460_hw_adc_awd_entry (void    *p_hw_adc,
                                     int      int_num_eoc,
                                     int      int_num_seqcmp,
                                     uint8_t  chan,
                                     uint32_t vref_mv);


/**
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio  ָ�� GPIO����Ĵ������ָ��
 * \param[in] input_pin  �������ź�
 * \param[in] output_pin ������ź�
 *
 * \return ��
 */
void demo_hc32f460_hw_gpio_entry (void    *p_hw_gpio,
                                  int32_t  input_pin,
                                  int32_t  output_pin);

/**
 * \brief GPIO �����ж����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_gpio     ָ�� GPIO ����Ĵ������ָ��
 * \param[in] pin           �ж����ź�
 *
 * \return ��
 */
void demo_hc32f460_hw_gpio_trigger_entry (void *p_hw_gpio, int pin);


/**
 * \brief DMA �ڴ浽�ڴ����̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] dma_chan DMA ͨ����
 *
 * \return ��
 */
void demo_hc32f460_drv_dma_m2m_entry (uint32_t dma_chan);

/**
 * \brief DMA �ڴ浽�ڴ������������̣�ͨ��������ӿ�ʵ��
 *
 * \param[in] p_dev    DMA �豸ָ��
 * \param[in] dma_chan DMA ͨ����
 *
 * \return ��
 */
void demo_hc32f460_drv_dma_m2m_chain_entry (am_hc32f460_dma_dev_t *p_dev, uint32_t dma_chan);

/**
 * \brief UART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] pfn_init  ָ�� UART ���ų�ʼ��������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 * \param[in] uart_base UART ����ַ
 * \param[in] inum_uart UART �жϺ�
 *
 * \return ��
 */
void demo_hc32f460_hw_uart_int_entry (void             *p_hw_uart,
                                      void (* pfn_init)(void),
                                      int              clk_rate,
                                      unsigned long    uart_base);

/**
 * \brief UART ��ѯ��ʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_hc32f460_hw_uart_polling_entry (void     *p_hw_uart,
                                          uint32_t  clk_rate);


/**
 * \brief UART DMA�������̣�ͨ�� HW ��ӿ�ʵ��
 *

 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_hc32f460_hw_uart_tx_dma_entry (void                   *p_hw_uart,
                                         uint32_t                clk_rate,
                                         am_hc32f460_dma_dev_t  *p_dma_dev,
                                         int32_t                 dma_chan);
/**
 * \brief UART DMA�������̣�ͨ�� HW ��ӿ�ʵ��
 *

 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] clk_rate  UART ʱ��ԴƵ��
 *
 * \return ��
 */
void demo_hc32f460_hw_uart_rx_dma_entry (void    *p_hw_uart,
                                         uint32_t clk_rate,
                                         am_hc32f460_dma_dev_t *p_dma_dev,
                                         int32_t  dma_chan);

/**
 * \brief QSPI��д��������
 *
 * \param[in] p_hw_uart ָ�� QSPI�豸��ָ��
 *
 * \return ��
 */
void demo_hc32f460_drv_qspi_entry (am_hc32f460_qspi_dev_t *p_dev);

/**
 * \brief SPI �������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * \param[in] p_hw_uart ָ�� UART ����Ĵ������ָ��
 * \param[in] cs_pin    Ƭѡ����
 *
 * \return ��
 */
void demo_hc32f460_hw_spi_master_entry (void    *p_hw_spi,
                                        int32_t  cs_pin);

#ifdef __cplusplus
}
#endif

#endif /* __DEMO_HC32F460_ENTRIES_H */

/* end of file */
