/*
 * Samsung Exynos SoC series FIMC-IS2 driver
 *
 * Copyright (c) 2015 Samsung Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef FIMC_IS_HW_CHAIN_V4_0_H
#define FIMC_IS_HW_CHAIN_V4_0_H

#include "fimc-is-groupmgr.h"
#include "fimc-is-config.h"

#define GROUP_HW_MAX	(GROUP_SLOT_MAX)

#define IORESOURCE_3AA0		2
#define IORESOURCE_3AA1		3
#define IORESOURCE_ISP0		4
#define IORESOURCE_ISP1		5
#define IORESOURCE_TPU		6
#define IORESOURCE_SCP		7
#define IORESOURCE_VRA_CH0	8
#define IORESOURCE_VRA_CH1	9

enum taaisp_chain_id {
	ID_3AA_0 = 0,
	ID_3AA_1 = 1,
	ID_ISP_0 = 2,
	ID_ISP_1 = 3,
	ID_TPU   = 4,
	ID_3AAISP_MAX
};

/* the number of interrupt source at each IP */
enum hwip_interrupt_map {
	INTR_HWIP1 = 0,
	INTR_HWIP2 = 1,
	INTR_HWIP_MAX
};

/* Specific interrupt map belonged to each IP */

/* FIMC-Scaler */
enum scaler_interrupt_map {
	INTR_SCALER_FRAME_END			= 0,	/* FRAME_END_INTR [0] */
	INTR_SCALER_FRAME_START			= 4,	/* FRAME_START_INTR [4] */
	INTR_SCALER_SHADOW_CONDITION		= 8,	/* ShadowCondition_INTR [8] */
	INTR_SCALER_SHADOW_TRIGGER		= 16,	/* ShadowTrigger _INTR [16] */
	INTR_SCALER_SHADOW_TRIGGER_BYHW		= 12,	/* ShadowTriggerByHW _INTR [12] */
	INTR_SCALER_CORE_END			= 20,	/* CORE _END_INTR [20] */
	INTR_SCALER_CORE_START			= 24,	/* CORE_ START_INTR [24] */
	INTR_SCALER_OUTSTALL_BLOCKING		= 30,	/* OUTSTALLBLOCKING_INTR [30] */
	INTR_SCALER_STALL_BLOCKING		= 31,	/* STALLBLOCKING_INTR [31] */
	INTR_MAX_SCALER_MAP
};

enum vra_chain0_interrupt_map {
	CH0INT_CIN_FR_ST			= 0,	/* VSYNC rise - verified when CIN is active */
	CH0INT_CIN_FR_END			= 1,	/* VSYNC fall - verified when CIN is active */
	CH0INT_CIN_LINE_ST			= 2,	/* Not used - per line */
	CH0INT_CIN_LINE_END			= 3,	/* Not used - per line */
	CH0INT_CIN_SP_LINE			= 4,	/* On start of line defined by reg_cin2isp_int_row
							- Currently not used */
	CH0INT_CIN_ERR_SIZES			= 5,	/* Interrupt occurs as the error occurs
							- not used - CH0INT_FRAME_SIZE_ERROR is used instead */
	CH0INT_CIN_ERR_YUV_FORMAT		= 6,	/* For YUV444 - not all channels are valid,
							for 422 - Even & Odd data not match (e.g. YU match YV) */
	CH0INT_CIN_FR_ST_NO_ACTIVE		= 7,	/* VSYNC received when CH0 not enabled */
	CH0INT_DMA_IN_ERROR			= 8,	/* An error that is "read" by DMA controller.
							Not a control error. Should be reported to HOST. */
	CH0INT_DMA_IN_FLUSH_DONE		= 9,	/* When TRANS_STOP_REQ is set this interrupt should be set */
	CH0INT_DMA_IN_FR_END			= 10,	/* Finished operation */
	CH0INT_DMA_IN_INFO			= 11,	/* Stall / Frame Start while active / Track
							- see RW_reg_dma_info_int_vector_ofs. Not used. */
	CH0INT_OUT_DMA_ERROR			= 12,	/* An error that is "read" by DMA controller.
							Not a control error. Should be reported to HOST. */
	CH0INT_OUT_DMA_FLUSH_DONE		= 13,	/* When TRANS_STOP_REQ is set this interrupt should be set */
	CH0INT_OUT_DMA_FR_END			= 14,	/* Finished operation */
	CH0INT_OUT_DMA_INFO			= 15,	/* Stall / Frame Start while active / Track
							- see RW_reg_dma_info_int_vector_ofs. Not used. */
	CH0INT_RWS_TRIGGER			= 16,	/* Not used (In our code Trigger == Frame Start) */
	CH0INT_END_FRAME			= 17,	/* CIN + DMAs + ISP chain were finished */
	CH0INT_END_ISP_DMA_OUT			= 18,	/* ISP chain + DMA out were finished (doesn't include CIN) */
	CH0INT_END_ISP_INPUT			= 19,	/* ISP chain + CIN / Input DMAs were finished
							(doesn't include output) */
	CH0INT_FRAME_SIZE_ERROR			= 20,	/* Like CH0INT_CIN_ERR_SIZES
							but interrupt occurs when VSYNC falls */
	CH0INT_ERR_FR_ST_BEF_FR_END		= 21,	/* VSYNC received while previous frame is being processed.
							Might be a trigger for "no end isp" */
	CH0INT_ERR_FR_ST_WHILE_FLUSH		= 22,	/* Should be tested on end of TRANS_STOP */
	CH0INT_ERR_VRHR_INTERVAL_VIOLATION	= 23,	/* Violation of minimal delta Frame start to first data */
	CH0INT_ERR_HFHR_INTERVAL_VIOLATION	= 24,	/* Violation of minimal delta End line -> Next line */
	CH0INT_ERR_PYRAMID_OVERFLOW		= 25
};

enum vra_chain1_interrupt_map {
	CH1INT_IN_CONT_SP_LINE			= 0,	/* Reach RW_reg_ch1_interrupted_insruction +
							RW_reg_ch1_interrupted_line */
	CH1INT_IN_STOP_IMMED_DONE		= 1,	/* Stop immediate command is done. */
	CH1INT_IN_END_OF_CONTEXT		= 2,	/* The reason might be found in RW_reg_ch1_stop_cause */
	CH1INT_IN_START_OF_CONTEXT		= 3,	/* Not used. */
	CH1INT_END_LOAD_FEATURES		= 4,	/* Not used. */
	CH1INT_SHADOW_TRIGGER			= 5,	/* Not used. */
	CH1INT_OUT_DMA_OVERFLOW			= 6,	/* Some output results not written to memory */
	CH1INT_MAX_NUM_RESULTS			= 7,	/* RCCs found more than maximal number of results
							- some results not sent to DMA */
	CH1INT_IN_DMA_ERROR			= 8,
	CH1INT_IN_DMA_FLUSH_DONE		= 9,	/* Not used. HW responsibility to check */
	CH1INT_IN_DMA_FR_END			= 10,	/* Finished operation */
	CH1INT_IN_DMA_INFO			= 11,	/* Stall / Frame Start while active / Track
							- see RW_reg_dma_info_int_vector_ofs */
	CH1INT_RES_DMA_ERROR			= 12,
	CH1INT_RES_DMA_FLUSH_DONE		= 13,	/* Not used. HW responsibility to check */
	CH1INT_RES_DMA_FR_END			= 14,	/* Finished operation */
	CH1INT_RES_DMA_INFO			= 15,	/* Stall / Frame Start while active / Track
							- see RW_reg_dma_info_int_vector_ofs */
	CH1INT_WATCHDOG				= 16	/* Watchdog timer expired => RCC is assumed to be stack */
};
#endif
