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
 * \brief GPIO����������GPIO��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-22  ipk,first implementation
 * \endinternal
 */

#include <am_hc32f460_gpio.h>
#include <am_hc32f460_gpio_util.h>
#include "am_gpio_util.h"
#include "am_gpio.h"
#include "am_int.h"
#include "am_bitops.h"
//#include "hw/amhw_zmf159_exti.h"
//#include "zmf159_pin.h"

/*******************************************************************************
* ˽�ж���
*******************************************************************************/

/** \brief �ж�δ���ӱ�ʶ */
#define AM_HC32F460_GPIO_INVALID_PIN_MAP    0xFF

/** \brief ����ָ��GPIO�豸��Ϣ��ָ�� */
#define __GPIO_DEVINFO_DECL(p_gpio_devinfo, p_dev)  \
        const am_hc32f460_gpio_devinfo_t *p_gpio_devinfo = p_dev->p_devinfo

/******************************************************************************
  ȫ�ֱ���
******************************************************************************/

/** \bruef ָ��GPIO�豸��ָ�� */
am_hc32f460_gpio_dev_t *__gp_gpio_dev;

/**
 * \brief �ⲿ�ж���0�жϺ���
 */
static void __port_exit0_int_isr (void * p_arg)
{

}

/**
 * \brief �ⲿ�ж���1�жϺ���
 */
static void __port_exit1_int_isr (void * p_arg)
{

}

/**
 * \brief �ⲿ�ж���2�жϺ���
 */
static void __port_exit2_int_isr (void * p_arg)
{

}

/**
 * \brief �ⲿ�ж���2�жϺ���
 */
static void __port_exit3_int_isr (void * p_arg)
{

}

/**
 * \brief �ⲿ�ж���4�жϺ���
 */
static void __port_exit4_int_isr (void * p_arg)
{

}

/**
 * \brief �ⲿ�ж���9_5�жϺ���
 */
static void __port_exit9_5_int_isr (void * p_arg)
{

}

/**
 * \brief �ⲿ�ж���5_10�жϺ���
 */
static void __port_exit15_10_int_isr (void * p_arg)
{

}

/*******************************************************************************
  ��������
*******************************************************************************/

/**
 * \brief ���Ź�������
 *
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] flags     : ���Ź���
 *
 * \return AM_OK     �����óɹ�
 */
int am_gpio_pin_cfg (int pin, uint32_t flags)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    /* IO�ڷ��� */
    uint8_t dir = 0;
    uint32_t func = 0, mode = 0;
    amhw_hc32f460_gpio_t *p_hw_gpio  = NULL;
    amhw_hc32f460_gpio_mode_t pin_mode   = AMHW_HC32F460_GPIO_MODE_IPU;

    uint8_t pin_pos = 0u;
    en_portx_t en_portx = AMHW_HC32F460_GPIO_PORT_A;

    if (__gp_gpio_dev == NULL) {
        return -AM_ENXIO;
    }
    
    __pin_calc(pin, &en_portx, &pin_pos);
    p_hw_gpio = (amhw_hc32f460_gpio_t*)p_gpio_devinfo->gpio_regbase;

    func      = AM_GPIO_COM_FUNC_GET(flags);
    mode      = AM_GPIO_COM_MODE_GET(flags);

    /* ��׼����� */
    if (func != AM_GPIO_FUNC_INVALID_VAL) {
        /* ʹ�ñ�׼��ǰ���˻�����ΪGPIOģʽ */
        if (amhw_hc32f460_gpio_pin_afr_get(p_hw_gpio, pin) != AMHW_HC32F460_AFIO_GPIO) {

            /* ���ù��ܻص�Ĭ��״̬������ʹ��GPIO���� */
            amhw_hc32f460_gpio_pin_afr_set(p_hw_gpio, AMHW_HC32F460_AFIO_GPIO, pin);

        }

        switch (func) {

        case AM_GPIO_INPUT_VAL:
            amhw_hc32f460_gpio_pin_dir_input(p_hw_gpio, pin);
            break;

        case AM_GPIO_OUTPUT_INIT_HIGH_VAL:
            /* ������� */
            amhw_hc32f460_gpio_pin_mode_set(p_hw_gpio,
                                          AMHW_HC32F460_GPIO_MODE_OUT_PP,
                                          pin);
            /* ����ߵ�ƽ */                                          
            amhw_hc32f460_gpio_pin_out_high(p_hw_gpio, pin);
            break;

        case AM_GPIO_OUTPUT_INIT_LOW_VAL:
            /* ������� */
            amhw_hc32f460_gpio_pin_mode_set(p_hw_gpio,
                                          AMHW_HC32F460_GPIO_MODE_OUT_PP,
                                          pin);

            /* ����͵�ƽ */
            amhw_hc32f460_gpio_pin_out_low(p_hw_gpio, pin);
            break;

        default:
            return -AM_ENOTSUP;
        }
    }
    
    /* ��ȡ����������� */
    
    if (mode != AM_GPIO_MODE_INVALID_VAL) {
        dir = amhw_hc32f460_gpio_pin_dir_get(p_hw_gpio, pin);

        switch (mode) {              
        case AM_GPIO_PULL_UP_VAL:
            if (dir != 1) {
                /* ��������ģʽ  */
                pin_mode = AMHW_HC32F460_GPIO_MODE_IPU;
            } else {
                /* ���û������ģʽ������Ϊ����ģʽ */
                pin_mode = AMHW_HC32F460_GPIO_MODE_OUT_PP;
            }
            break;

        case AM_GPIO_PULL_DOWN_VAL:  //HC32F46X cannot Support 
            break;

        case AM_GPIO_FLOAT_VAL:    //HC32F46X cannot Support 
            if (dir != 1) {
                pin_mode = AMHW_HC32F460_GPIO_MODE_IN_FLOATING;
            } else {
                /* ���û�и���ģʽ������Ϊ��©ģʽ */
                pin_mode = AMHW_HC32F460_GPIO_MODE_OUT_OD;
            }
            break;

        case AM_GPIO_OPEN_DRAIN_VAL:
            if (dir != 1) {
                /* ����û�п�©ģʽ������Ϊ���� */
                pin_mode = AMHW_HC32F460_GPIO_MODE_IN_FLOATING;
            } else {
                pin_mode = AMHW_HC32F460_GPIO_MODE_OUT_OD;
            }

            break;

        case AM_GPIO_PUSH_PULL_VAL:
            if (dir != 1) {
                /* ����û������ģʽ������Ϊ���� */
                pin_mode = AMHW_HC32F460_GPIO_MODE_IPU;
            } else {
                pin_mode = AMHW_HC32F460_GPIO_MODE_OUT_PP;
            }
            break;

        default:
            return -AM_ENOTSUP;
        }        
        amhw_hc32f460_gpio_pin_mode_set(p_hw_gpio, pin_mode, pin);
    }

    /*
     * ƽ̨�������
     */

    /* �ܽŵ�ģʽ */
    if ((flags & AM_HC32F460_GPIO_MODE) != 0) {

       switch (AM_ZMF159_GPIO_MODE_GET(flags)) {

       case 0:
           /* �������� */
           pin_mode = AMHW_HC32F460_GPIO_MODE_AIN;
           break;

       case 1:
           /* �������� */       
           pin_mode = AMHW_HC32F460_GPIO_MODE_IN_FLOATING;       
           break;

       case 2:  
           /* ��������ģʽ  */
           pin_mode = AMHW_HC32F460_GPIO_MODE_IPD;                             
           break;

       case 3:
           /* ��������ģʽ  */
           pin_mode = AMHW_HC32F460_GPIO_MODE_IPU;                  
           break;

       case 4:
           /* ͨ���������ģʽ */
           pin_mode = AMHW_HC32F460_GPIO_MODE_OUT_PP;                  
           break;

       case 5:
           /* ��©���ģʽ */
           pin_mode = AMHW_HC32F460_GPIO_MODE_OUT_OD;
           break;

       case 6:   
           /* �����������ģʽ */
           pin_mode = AMHW_HC32F460_GPIO_MODE_AOUT;
           break;

       case 7:  
           /* ���ÿ�©���ģʽ */
           pin_mode = AMHW_HC32F460_GPIO_MODE_AF_PP;
           break;
           
       case 8:  
           /* ���ÿ�©���ģʽ */
           pin_mode = AMHW_HC32F460_GPIO_MODE_AF_OD;
           break;

       default:
           return -AM_ENOTSUP;
       }       
       amhw_hc32f460_gpio_pin_mode_set(p_hw_gpio, pin_mode, pin);
    }

    /* ���ùܽŵ�������� */
    if ((flags & AM_HC32F460_GPIO_OUTRES_RATE) != 0) {
        amhw_hc32f460_gpio_pin_driver_capability(p_hw_gpio, AM_ZMF159_GPIO_OUTRES_RATE_GET(flags), pin);
    }

    /* ���ùܽŵĸ��ù��� */
    if ((flags & AM_HC32F460_GPIO_FUNEN) != 0) {
        amhw_hc32f460_gpio_pin_afr_set(p_hw_gpio, AM_ZMF159_GPIO_FUNC_GET(flags), pin);
    }
    return AM_OK;
}

/**
 * \brief ��ȡ����״̬
 *
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 *
 * \return ��
 */
int am_gpio_get (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_hc32f460_gpio_t *p_hw_gpio = (amhw_hc32f460_gpio_t *)p_gpio_devinfo->gpio_regbase;

    return amhw_hc32f460_gpio_pin_get(p_hw_gpio, pin);
}

/**
 * \brief �����������״̬
 *
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIOA_0)
 * \param[in] value     : ����ֵ
 *
 * \return AM_OK     �����óɹ�
 */
int am_gpio_set (int pin, int value)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_hc32f460_gpio_t *p_hw_gpio = (amhw_hc32f460_gpio_t *)p_gpio_devinfo->gpio_regbase;

    if (value == 0) {
        amhw_hc32f460_gpio_pin_out_low(p_hw_gpio, pin);
    } else {
        amhw_hc32f460_gpio_pin_out_high(p_hw_gpio, pin);

    }
    return AM_OK;
}

/**
 * \brief �������״̬��ת
 */
int am_gpio_toggle (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    amhw_hc32f460_gpio_t *p_hw_gpio = (amhw_hc32f460_gpio_t *)p_gpio_devinfo->gpio_regbase;

    amhw_hc32f460_gpio_pin_toggle(p_hw_gpio, pin);

    return AM_OK;
}

/**
 * \brief ���Ŵ�����ʽ����
 */
int am_gpio_trigger_cfg (int pin, uint32_t flag)
{
    return AM_OK;
}

/**
 * \brief ʹ�������жϡ�
 */
int am_gpio_trigger_on (int pin)
{
    return AM_OK;
}

/**
 * \brief ���������жϡ�
 */
int am_gpio_trigger_off (int pin)
{
    return AM_OK;
}

/**
 * \brief ���������жϻص�����
 */
int am_gpio_trigger_connect (int           pin,
                             am_pfnvoid_t  pfn_callback,
                             void         *p_arg)
{
     return AM_OK;
}

/**
 * \brief ɾ�������жϻص���������
 */
int am_gpio_trigger_disconnect (int           pin,
                                am_pfnvoid_t  pfn_callback,
                                void         *p_arg)
{
    return AM_OK;
}

/**
 * \brief GPIO��ʼ��
 *
 * \param[in] p_dev     : ָ��GPIO�豸��ָ��
 * \param[in] p_devinfo : ָ��GPIO�豸��Ϣ��ָ��
 *
 * \retval AM_OK : �����ɹ�
 */
int am_hc32f460_gpio_init (am_hc32f460_gpio_dev_t           *p_dev,
                           const am_hc32f460_gpio_devinfo_t *p_devinfo)
{
    uint8_t i = 0;

    if (NULL == p_dev || NULL == p_devinfo) {
        return -AM_EINVAL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->p_devinfo = p_devinfo;

    if ((p_devinfo->inum_pin == NULL)  ||
        (p_devinfo->p_infomap == NULL) ||
        (p_devinfo->p_triginfo == NULL)) {
        p_dev->valid_flg = AM_FALSE;
        return -AM_EINVAL;
    }

//    for (i = 0 ; i < p_devinfo->pin_count ; i++) {
//        if ((i == PIOA_13) || (i == PIOA_14) || (i == PIOA_15) ||
//             (i == PIOB_3) || (i == PIOB_4)) {
//            p_devinfo->p_remap[i] = AMHW_ZLG217_SWJ_CFG;
//        } else {
//            p_devinfo->p_remap[i] = AMHW_ZLG217_NO_REMAP;
//        }
//    }

    for (i = 0 ; i < p_devinfo->exti_num_max ; i++) {
        p_devinfo->p_infomap[i] = AM_HC32F460_GPIO_INVALID_PIN_MAP;
        p_devinfo->p_triginfo[i].p_arg = NULL;
        p_devinfo->p_triginfo[i].pfn_callback = NULL;
    }

//    am_int_connect(p_devinfo->inum_pin[0], __port_exit0_int_isr, NULL);
//    am_int_connect(p_devinfo->inum_pin[1], __port_exit1_int_isr, NULL);
//    am_int_connect(p_devinfo->inum_pin[2], __port_exit2_int_isr, NULL);
//    am_int_connect(p_devinfo->inum_pin[3], __port_exit3_int_isr, NULL);
//    am_int_connect(p_devinfo->inum_pin[4], __port_exit4_int_isr, NULL);

//    am_int_connect(p_devinfo->inum_pin[5], __port_exit9_5_int_isr, NULL);
//    am_int_connect(p_devinfo->inum_pin[6], __port_exit15_10_int_isr, NULL);

//    am_int_enable(p_devinfo->inum_pin[0]);
//    am_int_enable(p_devinfo->inum_pin[1]);
//    am_int_enable(p_devinfo->inum_pin[2]);
//    am_int_enable(p_devinfo->inum_pin[3]);
//    am_int_enable(p_devinfo->inum_pin[4]);
//    am_int_enable(p_devinfo->inum_pin[5]);
//    am_int_enable(p_devinfo->inum_pin[6]);

    p_dev->valid_flg = AM_TRUE;

    __gp_gpio_dev = p_dev;

    return AM_OK;
}

/**
 * \brief GPIOȥ��ʼ��
 *
 * \param[in] ��
 *
 * \return ��
 */
void am_hc32f460_gpio_deinit (void)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);

    int i = 0;

    if (__gp_gpio_dev->valid_flg) {
        for (i = 0; i < p_gpio_devinfo->exti_num_max; i++) {
            (p_gpio_devinfo->p_infomap)[i]               = AM_HC32F460_GPIO_INVALID_PIN_MAP;
            (p_gpio_devinfo->p_triginfo)[i].pfn_callback = NULL;
        }
    }

//    am_int_disable((p_gpio_devinfo->inum_pin)[0]);
//    am_int_disable((p_gpio_devinfo->inum_pin)[1]);
//    am_int_disable((p_gpio_devinfo->inum_pin)[2]);

//    am_int_disconnect(p_gpio_devinfo->inum_pin[0], __port_exit0_int_isr, NULL);
//    am_int_disconnect(p_gpio_devinfo->inum_pin[1], __port_exit1_int_isr, NULL);
//    am_int_disconnect(p_gpio_devinfo->inum_pin[2], __port_exit2_int_isr, NULL);
//    am_int_disconnect(p_gpio_devinfo->inum_pin[3], __port_exit3_int_isr, NULL);
//    am_int_disconnect(p_gpio_devinfo->inum_pin[4], __port_exit4_int_isr, NULL);

//    am_int_disconnect(p_gpio_devinfo->inum_pin[5], __port_exit9_5_int_isr, NULL);
//    am_int_disconnect(p_gpio_devinfo->inum_pin[6], __port_exit15_10_int_isr, NULL);

    if (__gp_gpio_dev->p_devinfo->pfn_plfm_deinit) {
        __gp_gpio_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
