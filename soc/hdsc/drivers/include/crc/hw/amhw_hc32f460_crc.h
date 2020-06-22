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
 * \brief CRC Peripheral Access Layer
 *
 * \internal
 * \par Modification history
 * - 1.00 20-05-18
 *
 * \endinternal
 */

#ifndef __AMHW_HC32F460_CRC_H
#define __AMHW_HC32F460_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"

/**
 * \addtogroup amhw_hc32f460_if_crc
 * \copydoc amhw_hc32f460_crc.h
 * @{
 */

/**
 * \brief ʹ������������ο�ʼ
 * @{
 */

#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)

/* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

/* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/** @} */

/**
 * \brief CRC - �Ĵ����ṹ��
 */

typedef struct
{
    uint32_t RESERVED0                      : 1;
    __IO uint32_t SEL                       : 1;
    __IO uint32_t REFIN                     : 1;
    __IO uint32_t REFOUT                    : 1;
    __IO uint32_t XOROUT                    : 1;
    uint32_t RESERVED5                      :27;
} stc_crc_cr_field_t;

typedef struct
{
    __IO uint32_t FLAG                      : 1;
    uint32_t RESERVED1                      :31;
} stc_crc_flg_field_t;

typedef struct amhw_hc32f460_crc {
    union
    {
        __IO uint32_t CR;
        stc_crc_cr_field_t CR_f;
    };
    __IO uint32_t RESLT;
    uint8_t RESERVED2[4];
    union
    {
        __IO uint32_t FLG;
        stc_crc_flg_field_t FLG_f;
    };
    uint8_t RESERVED3[112];
    __IO uint32_t DAT0;
    __IO uint32_t DAT1;
    __IO uint32_t DAT2;
    __IO uint32_t DAT3;
    __IO uint32_t DAT4;
    __IO uint32_t DAT5;
    __IO uint32_t DAT6;
    __IO uint32_t DAT7;
    __IO uint32_t DAT8;
    __IO uint32_t DAT9;
    __IO uint32_t DAT10;
    __IO uint32_t DAT11;
    __IO uint32_t DAT12;
    __IO uint32_t DAT13;
    __IO uint32_t DAT14;
    __IO uint32_t DAT15;
    __IO uint32_t DAT16;
    __IO uint32_t DAT17;
    __IO uint32_t DAT18;
    __IO uint32_t DAT19;
    __IO uint32_t DAT20;
    __IO uint32_t DAT21;
    __IO uint32_t DAT22;
    __IO uint32_t DAT23;
    __IO uint32_t DAT24;
    __IO uint32_t DAT25;
    __IO uint32_t DAT26;
    __IO uint32_t DAT27;
    __IO uint32_t DAT28;
    __IO uint32_t DAT29;
    __IO uint32_t DAT30;
    __IO uint32_t DAT31;
} amhw_hc32f460_crc_t;

/**
 * \brief CRC 32λд����
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 * \param[in] data     : ����У�������
 *
 * retval : none
 */
am_static_inline
void amhw_hc32f460_crc_32bit_write_data (amhw_hc32f460_crc_t    *p_hw_crc,
                                         uint32_t              data)
{
    p_hw_crc->DAT0 = data;
}

/**
 * \brief CRC 16λд����
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 * \param[in] data     : ����У�������
 *
 * retval : none
 *
 * \note this register can not  caculate data
 */
am_static_inline
void amhw_hc32f460_crc_16bit_write_data (amhw_hc32f460_crc_t  *p_hw_crc,
                                         uint16_t            data)
{
    uint32_t addr = (uint32_t)&p_hw_crc->DAT0;
    *(volatile uint16_t *)addr =  data;
}


/**
 * \brief CRC 32λУ�鷽ʽ��ʼ������Ĵ���ֵ
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 *
 * \retval : none
 */
am_static_inline
void amhw_hc32f460_crc_res_32data_init (amhw_hc32f460_crc_t *p_hw_crc, uint32_t value)
{
    p_hw_crc->RESLT = value;

}

/**
 * \brief CRC 16λУ�鷽ʽ��ʼ������Ĵ���ֵ
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 *
 * \retval : none
 */
am_static_inline
void amhw_hc32f460_crc_res_16data_init (amhw_hc32f460_crc_t *p_hw_crc, uint16_t value)
{
    uint32_t addr = (uint32_t)&p_hw_crc->RESLT;
    *(volatile uint16_t *)addr =  value;
}

/**
 * \brief CRC 32λ������
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 *
 * \retval : CRC������ֵ
 */
am_static_inline
uint32_t amhw_hc32f460_crc_32bit_read_data (amhw_hc32f460_crc_t *p_hw_crc)
{
    return (p_hw_crc->RESLT);
}

/**
 * \brief CRC 16λ������
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 *
 * \retval : CRC������ֵ
 */
am_static_inline
uint16_t amhw_hc32f460_crc_16bit_read_data (amhw_hc32f460_crc_t *p_hw_crc)
{
    return (uint16_t)(p_hw_crc->RESLT & 0xFFFF);
}

/**
 * \brief CRC У���ж�
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 *
 * \retval : none
 */
am_static_inline
uint32_t amhw_hc32f460_crc_judge (amhw_hc32f460_crc_t *p_hw_crc)
{
    return (p_hw_crc->FLG_f.FLAG == 1) ? AM_TRUE : AM_FALSE;
}

typedef enum {
    AMHW_HC32F460_CRC_BITS_16 = 0,
    AMHW_HC32F460_CRC_BITS_32 = 1,
} amhw_hc32f460_crc_bits_t;

/**
 * \brief CRC ����λ��ѡ��
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 * \param[in] flag     : ����λ����־��amhw_hc32f460_crc_bits_t��
 *
 * \retval : none
 */
am_static_inline
void amhw_hc32f460_crc_bits_sel (amhw_hc32f460_crc_t *p_hw_crc, uint32_t flag)
{
    p_hw_crc->CR_f.SEL = flag;
}

/**
 * \brief CRC �������Ƿ�ȡ������
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 * \param[in] flag     : AM_TRUE��ȡ����/AM_FALSE����ȡ����
 *
 * \retval : none
 */
am_static_inline
void amhw_hc32f460_crc_xorout_sel (amhw_hc32f460_crc_t *p_hw_crc, am_bool_t flag)
{
    p_hw_crc->CR_f.XOROUT = flag;
}

/**
 * \brief CRC �������Ƿ�λ����
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 * \param[in] flag     : AM_TRUE������/AM_FALSE��������
 *
 * \retval : none
 */
am_static_inline
void amhw_hc32f460_crc_refout_sel (amhw_hc32f460_crc_t *p_hw_crc, am_bool_t flag)
{
    p_hw_crc->CR_f.REFOUT = flag;
}

/**
 * \brief CRC ���������Ƿ��ֽ��ڷ���
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ��������ַ
 * \param[in] flag     : AM_TRUE������/AM_FALSE��������
 *
 * \retval : none
 */
am_static_inline
void amhw_hc32f460_crc_refin_sel (amhw_hc32f460_crc_t *p_hw_crc, am_bool_t flag)
{
    p_hw_crc->CR_f.REFIN = flag;
}

/**
 * \brief ʹ������������ν���
 * @{
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)

/* ��������������ʹ�� */
#elif defined(__GNUC__)

/* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

/* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif
/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_HC32F460_CRC_H */

/* end of file */
