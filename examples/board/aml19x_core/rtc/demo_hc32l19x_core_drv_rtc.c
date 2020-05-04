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
 * \brief RTC ���̣�ͨ����׼�ӿں��м������㺯��ʵ��
 *
 * - ʵ������
 *   1. ÿ10�뷢��һ�������жϣ����ڲ���ӡ����ǰʱ����Ϣ��
 *   2. ���ĵ�11��21��0����������жϣ���ӡ����"alarm clock int!"��ʾ��Ϣ��
 *   3. ����am_hwconf_hc32l19x_rtc.c�ļ�������1Hz������ƣ���ʹ�ܣ�PIOB_14�����1Hz�ķ�����
 *   4. �ر�ʱ�Ӳ���������£����1Hz������ʵ��Ƶ�ʣ��������м���ʽ���㣺
 *           ppm = ��1Hz������ʵ��Ƶ�� - 1Hz��* 10^6
 *      ��������Ľ������am_hwconf_hc32l19x_rtc.c���豸��Ϣ��Ӧλ�ã������о����Ƿ�ʹ�ܸ��ٲ���ʱ�ӡ�
 *      ���롢���أ�����˿ڽ�������Ƚϸߵ�1Hz����
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_hc32l19x_std_rtc.c src_hc32l19x_std_rtc
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-17  zp, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_hc32l19x_std_rtc
 * \copydoc demo_hc32l19x_std_rtc.c
 */

/** [src_hc32l19x_std_rtc] */
#include "ametal.h"
#include "am_rtc.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_hc32_rtc.h"
#include "am_hc32.h"
#include "demo_aml19x_core_entries.h"

/** \brief ��ǰʱ�� */
static am_tm_t     __g_time;

/** \brief ָʾ�Ƿ��ȡ��ʱ�� */
static am_bool_t   __g_get_flag = AM_FALSE;

/** \brief ��ʼ��ʱ�� */
static am_tm_t     __g_init_time = {
    00,   /** 0  ��             */
    16,   /** 16 ��             */
    10,   /** 10 ʱ             */
    23,   /** 23 ��             */
    3,    /** 4 ��             */
    120,  /** 2020 ��     */
    4,    /** �� 4   */
    114,  /** �� ����ĵ� 114 �� */
    0,    /** ����ʱ         */
};

/**
 * \brief ���ڻص�����
 */
static void __rtc_period_callback (void *p_arg)
{
    am_rtc_handle_t rtc_handle = (am_rtc_handle_t )p_arg;

    if(am_rtc_time_get(rtc_handle, &__g_time) == AM_OK) {
        __g_get_flag = AM_TRUE;
    }
}

/**
 * \brief ���ӻص�����
 */
static void __rtc_alarm_callback (void *p_arg)
{
    (void)p_arg;
    AM_DBG_INFO("alarm clock int!\r\n");
}

/**
 * \brief �������
 */
void demo_zsl420_hw_rtc_int_entry (void)
{
    int             ret        = AM_OK;
    am_rtc_handle_t rtc_handle = am_hc32_rtc_inst_init();

    AM_DBG_INFO("demo zsl420 RTC entry!\r\n");

    /* ����ʱ�� */
    ret= am_rtc_time_set(rtc_handle, &__g_init_time);
    if(ret == AM_OK){
        AM_DBG_INFO("set time success \r\n");
    } else {
        AM_DBG_INFO("set time fail \r\n");
    }

    /* ���������жϻص����� */
    am_hc32_rtc_int_connect(
        rtc_handle,
        AM_HC32_RTC_INT_PERIOD,
        __rtc_period_callback,
        rtc_handle);
    /* ʹ�������ж� */
    am_hc32_rtc_int_enable(
        rtc_handle,
        AM_HC32_RTC_INT_PERIOD);

    /* ���� PRDX ���� */
    amhw_hc32_rtc_period_int_time_set(HC32_RTC, 10.0);
    /* ʹ�� PRDX ���趨�������ж�ʱ���� */
    amhw_hc32_rtc_period_int_time_set_enable(HC32_RTC, AM_TRUE);

    /* ��������ʱ��Ϊÿ��4 11:21:00 */
    amhw_hc32_rtc_hour_alarm_clock_set(HC32_RTC, 10);
    amhw_hc32_rtc_min_alarm_clock_set(HC32_RTC,  16);
    amhw_hc32_rtc_sec_alarm_clock_set(HC32_RTC,  25);
    amhw_hc32_rtc_week_alarm_clock_set(HC32_RTC, 4);

    /* ���������жϻص����� */
    am_hc32_rtc_int_connect(
        rtc_handle,
        AM_HC32_RTC_INT_ALARM,
        __rtc_alarm_callback,
        rtc_handle);
    /* ʹ�������ж� */
    am_hc32_rtc_int_enable(
        rtc_handle,
        AM_HC32_RTC_INT_ALARM);

    /* �������� */
    amhw_hc32_rtc_alarm_clock_enable(HC32_RTC, AM_TRUE);

    while(1) {

        am_mdelay(20);

        if(__g_get_flag != AM_TRUE) {
            continue;
        }

        AM_DBG_INFO(
            "%02d-%02d-%02d %02d:%02d:%02d %02d\n",
            __g_time.tm_year,
            __g_time.tm_mon,
            __g_time.tm_mday,
            __g_time.tm_hour,
            __g_time.tm_min,
            __g_time.tm_sec,
            __g_time.tm_wday);

        __g_get_flag =  AM_FALSE;
    }
}
/** [src_hc32l19x_std_rtc] */

/* end of file */
