/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief DMA ����ʵ��
 *
 * \internal
 * \par Modification history
 * - 1.00 20-02-27  cds, first implementation
 * \endinternal
 */

#include "am_hc32f460_dma.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "hc32f460_intctrl.h"
#include "hc32f460_irq_handle.h"

/*******************************************************************************
  ˽�ж���
*******************************************************************************/


/** \brief �ж�δ���ӱ�ʶ */
#define __INT_NOT_CONNECTED      0xFF

/** \brief ͨ��δ���ӱ�ʶ */
#define __CHAN_NOT_CONNECTED     0xFF

/** \brief ����ָ��DMA�豸��Ϣ��ָ�� */
#define __DMA_DEVINFO_DECL(p_dma_devinfo, p_dev)  \
        const am_hc32f460_dma_devinfo_t *p_dma_devinfo = p_dev->p_devinfo


/*******************************************************************************
  ��������
*******************************************************************************/

/* �������������� */
int am_hc32f460_dma_xfer_desc_build (amhw_hc32f460_dma_xfer_desc_t *p_desc,
                                     uint32_t                       src_addr,
                                     uint32_t                       dst_addr,
									 uint32_t                       nbytes,
									 uint32_t                       flags)
{
    if (p_desc == NULL) {
        return AM_ERROR;
    }

    if (nbytes > 0xFFFF) {
        return AM_ERROR;
    }

    p_desc->xfercfg  = flags;
    p_desc->src_addr = src_addr;
    p_desc->dst_addr = dst_addr;
    p_desc->nbytes   = nbytes;

    return AM_OK;
}

/* ��ʼDMA���� */
int am_hc32f460_dma_xfer_desc_chan_cfg (am_hc32f460_dma_dev_t            *p_dev,
		                                amhw_hc32f460_dma_xfer_desc_t    *p_desc,
                                        amhw_hc32f460_dma_transfer_type_t type,
                                        uint8_t                           chan)
{
	amhw_hc32f460_dma_t *p_hw_dma =
	    (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

	uint16_t count_trans = 0;
	uint16_t blk_size    = 0;
	uint16_t data_size   = 0;
	uint32_t reg_val     = 0;

    if (p_desc == NULL) {
        return AM_ERROR;
    }

    if (chan > AMHW_HC32F460_DMA_CHAN_CNT) {
        return AM_ERROR;
    }

    switch(type) {

    case AMHW_HC32F460_DMA_PER_TO_MER:
    case AMHW_HC32F460_DMA_MER_TO_PER:
    case AMHW_HC32F460_DMA_MER_TO_MER:
    case AMHW_HC32F460_DMA_PER_TO_PER:
    	amhw_hc32f460_dma_chan_src_address_set(p_hw_dma,
    	                                       chan,
    	                                       p_desc->src_addr);

    	amhw_hc32f460_dma_chan_dst_address_set(p_hw_dma,
    	                                       chan,
    	                                       p_desc->dst_addr);
        break;

    default:
        break;
    }

    /* ��ȡָ��ͨ�����ݿ�Ĵ�С(Ĭ��һ����ֻ��1������) */
    reg_val = amhw_hc32f460_dma_chan_blksize_get(p_hw_dma, chan);
    if (reg_val == 0) {
    	blk_size = 1024;
    } else {
    	blk_size = reg_val;
    }

    /* ��ȡÿ�����ݵĴ�С(Ĭ��һ������ֻ��һ���ֽ�) */
    reg_val  = amhw_hc32f460_dma_chan_data_hsize_get(p_hw_dma, chan);
    switch (reg_val) {
    case 0 : data_size = 1;
             break;
    case 1 : data_size = 2;
             break;
    case 2 :
    case 3 : data_size = 4;
             break;
    }
    if ((count_trans % (blk_size * data_size)) == 0) {
    	count_trans = p_desc->nbytes / (blk_size * data_size);
    } else {
    	return -AM_EINVAL;
    }

    amhw_hc32f460_dma_chan_tran_data_num_set(p_hw_dma,
                                             chan,
                                             p_desc->nbytes);

    amhw_hc32f460_dma_chan_config_set(p_hw_dma,
                                      chan,
                                      p_desc->xfercfg);

    return AM_OK;
}

/* ������������������ */
int am_hc32f460_dma_chain_xfer_desc_build (amhw_hc32f460_dma_chain_xfer_desc_t *p_desc,   /* �������ṹ��ָ���ַ */
                                           uint32_t                             src_addr,
                                           uint32_t                             dst_addr,
							               uint32_t                             count,
                                           uint32_t                             blk_size,
                                           uint32_t                             drpt,
                                           uint32_t                             srpt,
                                           uint32_t                             snscnt,
                                           uint32_t                             soffset,
                                           uint32_t                             dnscnt,
                                           uint32_t                             dsoffset,
                                           uint32_t                             link,
                                           uint32_t                             ch_ctl)
{
    if (p_desc == NULL) {
        return AM_ERROR;
    }

    if ((count > 0xFFFF)    ||
    	(blk_size > 0x3FF)  ||
		(drpt > 0x3FF)      ||
		(srpt > 0x3FF)      ||
		(snscnt > 0xFFF)    ||
		(soffset > 0xFFFFF) ||
		(dnscnt > 0xFFF)    ||
		(dsoffset > 0xFFFFF)||
		((link & 0x3) != 0)) {
    	return -AM_EINVAL;
    }

    p_desc->src_addr  = src_addr;
    p_desc->dst_addr  = dst_addr;
    p_desc->data_ctrl = (count << 16) | blk_size;
    p_desc->rpt       = (drpt << 16) | srpt;
    p_desc->snseqctl  = (snscnt << 20) | soffset;
    p_desc->dnseqctl  = (dnscnt << 20) | dsoffset;
    p_desc->llp       = link;
    p_desc->ch_ctl    = ch_ctl;

    return AM_OK;
}

/* DMA������������ */
int am_hc32f460_dma_chain_xfer_desc_chan_cfg (am_hc32f460_dma_dev_t                  *p_dev,
		                                      amhw_hc32f460_dma_chain_xfer_desc_t    *p_desc,
                                              amhw_hc32f460_dma_transfer_type_t       type,
                                              uint8_t                                 chan)
{
	amhw_hc32f460_dma_t *p_hw_dma =
	    (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

	switch(type) {

	    case AMHW_HC32F460_DMA_PER_TO_MER:
	    case AMHW_HC32F460_DMA_MER_TO_PER:
	    case AMHW_HC32F460_DMA_MER_TO_MER:
	    case AMHW_HC32F460_DMA_PER_TO_PER:
	    	amhw_hc32f460_dma_chan_src_address_set(p_hw_dma,
	    	                                       chan,
	    	                                       p_desc->src_addr);

	    	amhw_hc32f460_dma_chan_dst_address_set(p_hw_dma,
	    	                                       chan,
	    	                                       p_desc->dst_addr);
	        break;

	    default:
	        break;
	    }


	amhw_hc32f460_dma_chan_dtctl_set(p_hw_dma, chan, p_desc->data_ctrl);
	amhw_hc32f460_dma_chan_rpt_set(p_hw_dma, chan, p_desc->rpt);
	amhw_hc32f460_dma_chan_snseqctl_set(p_hw_dma, chan, p_desc->snseqctl);
	amhw_hc32f460_dma_chan_dnseqctl_set(p_hw_dma, chan, p_desc->dnseqctl);
	amhw_hc32f460_dma_chan_llp_set(p_hw_dma, chan, p_desc->llp);
	amhw_hc32f460_dma_chan_config_set(p_hw_dma, chan, p_desc->ch_ctl);
}



/* �趨ͨ������Ĵ���Դ����鿴hc32f460_dma_chan.h�궨�壩*/
void am_hc32f460_dma_chan_src_set (am_hc32f460_dma_dev_t *p_dev, int chan, en_event_src_t src)
{
	amhw_hc32f460_dma_t *p_hw_dma =
	    (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

    amhw_hc32f460_dma_chan_trigger_src_set(p_hw_dma,p_dev->p_devinfo->id, chan, src);
}

/* �趨ͨ����������Ĵ���Դ����鿴hc32f460_dma_chan.h�궨�壩*/
void am_hc32f460_dma_chan_rcfg_src_set (en_event_src_t src)
{
	amhw_hc32f460_dma_chan_rcfg_trigger_src_set(src);
}

/* ��ʼͨ������ */
int am_hc32f460_dma_chan_start (am_hc32f460_dma_dev_t *p_dev, int chan)
{
	amhw_hc32f460_dma_t *p_hw_dma =
	    (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

    amhw_hc32f460_dma_enable(p_hw_dma);

    amhw_hc32f460_dma_chan_enable(p_hw_dma, chan);

    return AM_OK;
}

/* ֹͣͨ������ */
int am_hc32f460_dma_chan_stop (am_hc32f460_dma_dev_t    *p_dev, int chan)
{
	amhw_hc32f460_dma_t *p_hw_dma =
	    (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

    amhw_hc32f460_dma_chan_int_disable(p_hw_dma,
                                       chan);

    amhw_hc32f460_dma_chan_disable(p_hw_dma, chan);

    return AM_OK;
}

/* DMA�жϴ����� */
void dma_int_handler (void *p_arg)
{
	am_hc32f460_dma_dev_t *p_dev = (am_hc32f460_dma_dev_t *)p_arg;

	amhw_hc32f460_dma_t *p_hw_dma =
        (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

    int      i;
    int      chan = 0xFF;
    uint8_t  flag = 0xFF;

    am_hc32f460_pfn_dma_isr_t  pfn_isr;
    void                      *p_isr_arg;


    for (i = 0 ; i < AMHW_HC32F460_DMA_CHAN_CNT; i++) {
    	    flag = AMHW_HC32F460_DMA_INT_FLAG_DEFAULT;
            chan = i;

        if (amhw_hc32f460_dma_chan_stat_check(
                p_hw_dma, i, AMHW_HC32F460_DMA_INT_FLAG_TX_COMPLETE) == AM_TRUE){

            flag = AM_HC32F460_DMA_INT_COMPLETE;
            amhw_hc32f460_dma_chan_flag_clear(p_hw_dma, i, AMHW_HC32F460_DMA_INT_FLAG_TX_COMPLETE);

        } else if (amhw_hc32f460_dma_chan_stat_check(
                p_hw_dma, i, AMHW_HC32F460_DMA_INT_FLAG_BLK_TX_COMPLETE) == AM_TRUE){

            flag = AM_HC32F460_DMA_INT_BLK_COMPLETE;
            amhw_hc32f460_dma_chan_flag_clear(p_hw_dma, i, AMHW_HC32F460_DMA_INT_FLAG_BLK_TX_COMPLETE);

        } else if (amhw_hc32f460_dma_chan_stat_check(
                p_hw_dma, i, AMHW_HC32F460_DMA_INT_FLAG_ERR_REQ_ERR) == AM_TRUE){

            flag = AM_HC32F460_DMA_INT_ERR_REQERR;
            amhw_hc32f460_dma_chan_flag_clear(p_hw_dma, i, AMHW_HC32F460_DMA_INT_FLAG_ERR_REQ_ERR);

        } else if (amhw_hc32f460_dma_chan_stat_check(
                p_hw_dma, i, AMHW_HC32F460_DMA_INT_FLAG_ERR_TRNERR) == AM_TRUE){

            flag = AM_HC32F460_DMA_INT_ERR_TRNERR;
            amhw_hc32f460_dma_chan_flag_clear(p_hw_dma, i, AMHW_HC32F460_DMA_INT_FLAG_ERR_TRNERR);

        }
        if (0xFF != chan) {

            pfn_isr   = p_dev->__dma_int_info[chan].pfn_isr;
            p_isr_arg = p_dev->__dma_int_info[chan].p_arg;

            if (pfn_isr) {
                pfn_isr(p_isr_arg , flag);
            }
        }
    }
}

/* ����DMA�жϷ����� */
int am_hc32f460_dma_isr_connect (am_hc32f460_dma_dev_t     *p_dev,
		                         int                        chan,
                                 am_hc32f460_pfn_dma_isr_t  pfn_isr,
                                 void                      *p_arg)
{
    if (p_dev->__dma_int_map[chan] == __INT_NOT_CONNECTED) {
    	p_dev->__dma_int_info[chan].pfn_isr = pfn_isr;
    	p_dev->__dma_int_info[chan].p_arg   = p_arg;
    	p_dev->__dma_int_map[chan]          = chan;
    } else {
        return -AM_EPERM;
    }

    return AM_OK;
}

/* ɾ��DMA�жϷ��������� */
int am_hc32f460_dma_isr_disconnect (am_hc32f460_dma_dev_t    *p_dev,
		                            int                       chan,
                                    am_hc32f460_pfn_dma_isr_t pfn_isr,
                                    void                     *p_arg)
{
    if (p_dev->__dma_int_map[chan] == chan) {
    	p_dev->__dma_int_info[chan].pfn_isr = NULL;
    	p_dev->__dma_int_map[chan]          = __INT_NOT_CONNECTED;
    } else {
        return -AM_EPERM;
    }

    return AM_OK;
}

/* ����ĳ�ж� */
void am_hc32f460_dma_chan_int_mask_set (am_hc32f460_dma_dev_t *p_dev, int chan, uint32_t int_flag)
{
	amhw_hc32f460_dma_t *p_hw_dma =
	    (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

	if (int_flag & AM_HC32F460_DMA_INT_ERR_REQERR) {
		amhw_hc32f460_dma_int_mask_set(p_hw_dma, chan, AMHW_HC32F460_DMA_INT_FLAG_ERR_REQ_ERR);
	}
	if (int_flag == AM_HC32F460_DMA_INT_ERR_TRNERR) {
		amhw_hc32f460_dma_int_mask_set(p_hw_dma, chan, AMHW_HC32F460_DMA_INT_FLAG_ERR_TRNERR);
	}
	if (int_flag == AM_HC32F460_DMA_INT_BLK_COMPLETE) {
		amhw_hc32f460_dma_int_mask_set(p_hw_dma, chan, AMHW_HC32F460_DMA_INT_FLAG_BLK_TX_COMPLETE);
	}
	if (int_flag == AM_HC32F460_DMA_INT_COMPLETE) {
		amhw_hc32f460_dma_int_mask_set(p_hw_dma, chan, AMHW_HC32F460_DMA_INT_FLAG_TX_COMPLETE);
	}
}

/* ���ĳ�жϵ����� */
void am_hc32f460_dma_chan_int_mask_clr (am_hc32f460_dma_dev_t *p_dev, int chan, uint32_t int_flag)
{
	amhw_hc32f460_dma_t *p_hw_dma =
	    (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

	if (int_flag & AMHW_HC32F460_DMA_INT_FLAG_ERR_REQ_ERR) {
		amhw_hc32f460_dma_int_mask_set(p_hw_dma, chan, AMHW_HC32F460_DMA_INT_FLAG_ERR_REQ_ERR);
	}
	if (int_flag == AMHW_HC32F460_DMA_INT_FLAG_ERR_TRNERR) {
		amhw_hc32f460_dma_int_mask_set(p_hw_dma, chan, AMHW_HC32F460_DMA_INT_FLAG_ERR_TRNERR);
	}
	if (int_flag == AMHW_HC32F460_DMA_INT_FLAG_BLK_TX_COMPLETE) {
		amhw_hc32f460_dma_int_mask_set(p_hw_dma, chan, AMHW_HC32F460_DMA_INT_FLAG_BLK_TX_COMPLETE);
	}
	if (int_flag == AMHW_HC32F460_DMA_INT_FLAG_TX_COMPLETE) {
		amhw_hc32f460_dma_int_mask_set(p_hw_dma, chan, AMHW_HC32F460_DMA_INT_FLAG_TX_COMPLETE);
	}
}

/**
 * \breif ��ȡĳͨ����ǰ����ʣ��Ĵ���
 */
uint16_t am_hc32f460_dma_tran_data_get (am_hc32f460_dma_dev_t *p_dev, int chan)
{
	amhw_hc32f460_dma_t *p_hw_dma =
        (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

    return amhw_hc32f460_dma_chan_tran_data_num_get(p_hw_dma, chan);
}

/**
 * \brief ���ô���Ĵ���(�����ֽ���=������� * ��������� * ÿ�����ݵĴ�С)
 */
void am_hc32f460_dma_tran_data_size (am_hc32f460_dma_dev_t *p_dev, int chan, uint32_t trans_data_byte)
{
	amhw_hc32f460_dma_t *p_hw_dma =
        (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

    amhw_hc32f460_dma_chan_tran_data_num_set(p_hw_dma,
                                             chan,
                                             trans_data_byte);
}

/**
 * \brief ����һ�����������
 */
void am_hc32f460_dma_block_data_size (am_hc32f460_dma_dev_t *p_dev, int chan, uint16_t block_data_num)
{
	amhw_hc32f460_dma_t *p_hw_dma =
        (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

    if (block_data_num == 1024) {
    	amhw_hc32f460_dma_chan_blksize_set(p_hw_dma,
    	                                   chan,
    	                                   0);
    } else if(block_data_num < 1024){
    	amhw_hc32f460_dma_chan_blksize_set(p_hw_dma,
    	    	                           chan,
									       block_data_num);
    }

}

/**
 * \brief ����Ŀ���ַ�ظ������С
 *        Ŀ���豸��ÿ����size�����ݺ�Ŀ���ַ����ΪDMA_DARx�Ĵ�����ֵ��
 */
int am_hc32f460_dma_drpt_size_set (am_hc32f460_dma_dev_t *p_dev, int chan, uint16_t size)
{
	amhw_hc32f460_dma_t *p_hw_dma =
        (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

    if (size > 0x3FF) {
        return -AM_EINVAL;
    } else {
    	amhw_hc32f460_dma_chan_drpt_size_set(p_hw_dma,
    	                                     chan,
											 size);
    }

    return AM_OK;
}


/**
 * \brief ����Դ��ַ�ظ������С
 *        Դ�豸��ÿ����size�����ݺ�Դ��ַ����ΪDMA_DARx�Ĵ�����ֵ��
 */
int am_hc32f460_dma_srpt_size_set (am_hc32f460_dma_dev_t *p_dev, int chan, uint16_t size)
{
	amhw_hc32f460_dma_t *p_hw_dma =
        (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

    if (size > 0x3FF) {
        return -AM_EINVAL;
    } else {
    	amhw_hc32f460_dma_chan_srpt_size_set(p_hw_dma,
    	                                     chan,
											 size);
    }

    return AM_OK;
}

/**
 * \brief Դ�豸��������ַ��������
 */
int am_hc32f460_dma_snseqctl_cfg (am_hc32f460_dma_dev_t *p_dev,
		                          int                    chan,
								  uint16_t               snscnt,
								  uint16_t               soffset)
{
	amhw_hc32f460_dma_t *p_hw_dma =
        (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

    if ((snscnt < 0xFFF) && (soffset < 0xFFFFF)) {
    	amhw_hc32f460_dma_chan_snseqctl_set(p_hw_dma, chan, (snscnt << 20) | (soffset));
    } else {
    	return -AM_EINVAL;
    }
}

/**
 * \brief Ŀ���豸��������ַ��������
 */
int am_hc32f460_dma_dnseqctl_cfg (am_hc32f460_dma_dev_t *p_dev,
		                          int                    chan,
								  uint16_t               dnscnt,
								  uint16_t               doffset)
{
	amhw_hc32f460_dma_t *p_hw_dma =
        (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

    if ((dnscnt < 0xFFF) && (doffset < 0xFFFFF)) {
    	amhw_hc32f460_dma_chan_dnseqctl_set(p_hw_dma, chan, (dnscnt << 20) | (doffset));
    } else {
    	return -AM_EINVAL;
    }
}


/**
 * \brief ͨ�����ÿ��ƼĴ�������
 */
void am_hc32f460_dma_chan_rcfg_set (am_hc32f460_dma_dev_t *p_dev,
		                            uint8_t                cntmd,
									uint8_t                darmd,
									uint8_t                sarmd,
									uint8_t                chan,
									uint8_t                rcfgllp,
									uint8_t                rcfgen)
{
	amhw_hc32f460_dma_t *p_hw_dma =
        (amhw_hc32f460_dma_t *) p_dev->p_devinfo->dma_reg_base;

	uint32_t flag = (cntmd << 20) |
			        (darmd << 18) |
					(sarmd << 16) |
					(chan  << 8 ) |
					(rcfgllp << 1) |
					(rcfgen);

    amhw_hc32f460_dma_chan_rcfg_set(p_hw_dma, flag);
}



/* DMA��ʼ�� */
int am_hc32f460_dma_init (am_hc32f460_dma_dev_t           *p_dev,
                          const am_hc32f460_dma_devinfo_t *p_devinfo)
{
    uint32_t i = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return AM_ERROR;
    }

    p_dev->p_devinfo = p_devinfo;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    for (i = 0; i < AMHW_HC32F460_DMA_CHAN_CNT; i++) {
    	p_dev->__dma_int_info[i].pfn_isr = NULL;
    	p_dev->__dma_int_map[i]          = __INT_NOT_CONNECTED;
    }

    /* ʹ�ܹ����ж�DMA���λ */
    if (p_dev->p_devinfo->id == 1) {
    	amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum, 0x10F0F);
    } else if (p_dev->p_devinfo->id == 2) {
    	amhw_hc32f460_intc_int_vssel_bits_set(p_dev->p_devinfo->inum, 0x2F0F0);
    }

    am_int_connect(p_devinfo->inum, IRQ129_Handler, (void *)0);
    am_int_enable(p_devinfo->inum);

    return AM_OK;
}

/* DMAȥ��ʼ�� */
void am_hc32f460_dma_deinit (am_hc32f460_dma_dev_t *p_dev)
{
    am_hc32f460_dma_devinfo_t *p_dma_devinfo = NULL;
    amhw_hc32f460_dma_t       *p_hw_dma;
    
    int i = 0;

    if (NULL == p_dev) {
        return;
    }

    p_dma_devinfo = (am_hc32f460_dma_devinfo_t *)p_dev->p_devinfo;
    p_hw_dma      = (amhw_hc32f460_dma_t *)p_dma_devinfo->dma_reg_base;

    for (i = 0; i < AMHW_HC32F460_DMA_CHAN_CNT; i++) {
    	p_dev->__dma_int_info[i].pfn_isr = NULL;
    	p_dev->__dma_int_map[i]          = 0;
        amhw_hc32f460_dma_chan_disable(p_hw_dma ,i);
    }

    /* ���ܹ����ж�DMA���λ */
    if (p_dev->p_devinfo->id == 1) {
    	amhw_hc32f460_intc_int_vssel_bits_clr(p_dev->p_devinfo->inum, 0x10F0F);
    } else if (p_dev->p_devinfo->id == 2) {
    	amhw_hc32f460_intc_int_vssel_bits_clr(p_dev->p_devinfo->inum, 0x2F0F0);
    }

    am_int_disconnect(p_dma_devinfo->inum, dma_int_handler, (void *)0);

    /* �����жϺ���ص������ж�Դ�Ĺ����ж϶������ܣ��ر��ж� */
    if (amhw_hc32f460_intc_int_vssel_get(p_dma_devinfo->inum) == 0) {
    	am_int_disable(p_dma_devinfo->inum);
    }

    if (p_dma_devinfo->pfn_plfm_deinit) {
        p_dma_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
