/**
 ******************************************************************************
 * @addtogroup Targets Target Boards
 * @{
 * @addtogroup SPRF3E SP Racing F3 Evo
 * @{
 *
 * @file       board_hw_defs.c 
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2011.
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2012-2014
 * @author     dRonin, http://dRonin.org/, Copyright (C) 2016
 * @brief      Defines board specific static initializers for hardware for the
 *             sprf3e board.
 * @see        The GNU Public License (GPL) Version 3
 * 
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>
 */

#include <pios.h>
#include <pios_config.h>
#include <pios_board_info.h>

#if defined(PIOS_INCLUDE_ANNUNC)

#include <pios_annunc_priv.h>
static const struct pios_annunc pios_annuncs[] = {
	[PIOS_LED_HEARTBEAT] = {
		.pin = {
			.gpio = GPIOC,
			.init = {
				.GPIO_Pin   = GPIO_Pin_14,
				.GPIO_Speed = GPIO_Speed_50MHz,
				.GPIO_Mode  = GPIO_Mode_OUT,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_NOPULL
			},
		},
		.active_high = false,
	},
	[PIOS_LED_ALARM] = {
		.pin = {
			.gpio = GPIOA,
			.init = {
				.GPIO_Pin   = GPIO_Pin_13,
				.GPIO_Speed = GPIO_Speed_50MHz,
				.GPIO_Mode  = GPIO_Mode_OUT,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_NOPULL
			},
		},
		.active_high = false,
	},
	[PIOS_ANNUNCIATOR_BUZZER] = {
		.pin = {
			.gpio = GPIOC,
			.init = {
				.GPIO_Pin   = GPIO_Pin_15,
				.GPIO_Speed = GPIO_Speed_50MHz,
				.GPIO_Mode  = GPIO_Mode_OUT,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_DOWN
			},
		},
		.active_high = false,
	},
};

static const struct pios_annunc_cfg pios_annunc_cfg = {
	.annunciators     = pios_annuncs,
	.num_annunciators = NELEMENTS(pios_annuncs),
};

const struct pios_annunc_cfg * PIOS_BOARD_HW_DEFS_GetLedCfg (uint32_t board_revision)
{
	return &pios_annunc_cfg;
}

#endif	/* PIOS_INCLUDE_ANNUNC */

#if defined(PIOS_INCLUDE_SPI)
#include <pios_spi_priv.h>
/*
 * SPI1 Interface
 * Used for gyro and accelerometer
 */
static const struct pios_spi_cfg pios_spi_gyro_cfg = {
	.regs = SPI1,
	.remap = GPIO_AF_5,
	.init = {
		.SPI_Mode              = SPI_Mode_Master,
		.SPI_Direction         = SPI_Direction_2Lines_FullDuplex,
		.SPI_DataSize          = SPI_DataSize_8b,
		.SPI_NSS               = SPI_NSS_Soft,
		.SPI_FirstBit          = SPI_FirstBit_MSB,
		.SPI_CRCPolynomial     = 7,
		.SPI_CPOL              = SPI_CPOL_High,
		.SPI_CPHA              = SPI_CPHA_2Edge,
		.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8,
	},
	.sclk = {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin = GPIO_Pin_5,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd = GPIO_PuPd_NOPULL
		},
		.pin_source = GPIO_PinSource5,
	},
	.miso = {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin = GPIO_Pin_6,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd = GPIO_PuPd_NOPULL
		},
		.pin_source = GPIO_PinSource6,
	},
	.mosi = {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin = GPIO_Pin_7,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd = GPIO_PuPd_NOPULL
		},
		.pin_source = GPIO_PinSource7,
	},
	.slave_count = 1,
	.ssel = { {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin = GPIO_Pin_4,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode  = GPIO_Mode_OUT,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd = GPIO_PuPd_UP
		},
	} },
};

/*
 * SPI2 Interface
 * Used for Flash chip
 */
static const struct pios_spi_cfg pios_spi_flash_cfg = {
	.regs   = SPI2,
	.remap = GPIO_AF_5,
	.init   = {
		.SPI_Mode              = SPI_Mode_Master,
		.SPI_Direction         = SPI_Direction_2Lines_FullDuplex,
		.SPI_DataSize          = SPI_DataSize_8b,
		.SPI_NSS               = SPI_NSS_Soft,
		.SPI_FirstBit          = SPI_FirstBit_MSB,
		.SPI_CRCPolynomial     = 7,
		.SPI_CPOL              = SPI_CPOL_Low,
		.SPI_CPHA              = SPI_CPHA_1Edge,
		.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4,
	},
	.sclk = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin = GPIO_Pin_13,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd = GPIO_PuPd_NOPULL
		},
		.pin_source = GPIO_PinSource13,
	},
	.miso = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin = GPIO_Pin_14,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd = GPIO_PuPd_NOPULL
		},
		.pin_source = GPIO_PinSource14,
	},
	.mosi = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin = GPIO_Pin_15,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd = GPIO_PuPd_NOPULL
		},
		.pin_source = GPIO_PinSource15,
	},
	.slave_count = 1,
	.ssel = { {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin = GPIO_Pin_12,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode  = GPIO_Mode_OUT,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd = GPIO_PuPd_UP
		},
	} },
};
#endif

#if defined(PIOS_INCLUDE_FLASH)
//taken mostly from OgBrain
#include "pios_flashfs_logfs_priv.h"

static const struct flashfs_logfs_cfg flashfs_settings_cfg = {
	.fs_magic      = 0x3bb141cf,
	.arena_size    = 0x00010000, /* 256 * slot size */
	.slot_size     = 0x00000100, /* 256 bytes */
};

#if defined(PIOS_INCLUDE_FLASH_JEDEC)
#include "pios_flash_jedec_priv.h"

static const struct pios_flash_jedec_cfg flash_m25p_cfg = {
	.expect_manufacturer = JEDEC_MANUFACTURER_ST,
	.expect_memorytype   = 0x20,
	.expect_capacity     = 0x15,
	.sector_erase        = 0xD8,
};
#endif	/* PIOS_INCLUDE_FLASH_JEDEC */

#include "pios_flash_internal_priv.h"

static const struct pios_flash_internal_cfg flash_internal_cfg = {
};

#include "pios_flash_priv.h"

static const struct pios_flash_sector_range stm32f3_sectors[] = {
	{
		.base_sector = 0,
		.last_sector = 127,
		.sector_size = FLASH_SECTOR_2KB,
	},
};

uintptr_t pios_internal_flash_id;
static const struct pios_flash_chip pios_flash_chip_internal = {
	.driver        = &pios_internal_flash_driver,
	.chip_id       = &pios_internal_flash_id,
	.page_size     = 16, /* 128-bit rows */
	.sector_blocks = stm32f3_sectors,
	.num_blocks    = NELEMENTS(stm32f3_sectors),
};

#if defined(PIOS_INCLUDE_FLASH_JEDEC)
static struct pios_flash_sector_range m25p16_sectors[] = {
	{
		.base_sector = 0,
		.last_sector = 31,
		.sector_size = FLASH_SECTOR_64KB,
	},
};

uintptr_t pios_external_flash_id;
static const struct pios_flash_chip pios_flash_chip_external = {
	.driver        = &pios_jedec_flash_driver,
	.chip_id       = &pios_external_flash_id,
	.page_size     = 256,
	.sector_blocks = m25p16_sectors,
	.num_blocks    = NELEMENTS(m25p16_sectors),
};
#endif /* PIOS_INCLUDE_FLASH_JEDEC */

static const struct pios_flash_partition pios_flash_partition_table[] = {
	{
		.label        = FLASH_PARTITION_LABEL_BL,
		.chip_desc    = &pios_flash_chip_internal,
		.first_sector = 0,
		.last_sector  = 7,
		.chip_offset  = 0,
		.size         = (7 - 0 + 1) * FLASH_SECTOR_2KB,
	},

	{
		.label        = FLASH_PARTITION_LABEL_FW,
		.chip_desc    = &pios_flash_chip_internal,
		.first_sector = 8,
		.last_sector  = 127,
		.chip_offset  = (8 * FLASH_SECTOR_2KB),
		.size         = (127 - 8 + 1) * FLASH_SECTOR_2KB,
	},

#if defined(PIOS_INCLUDE_FLASH_JEDEC)
	{
		.label        = FLASH_PARTITION_LABEL_SETTINGS,
		.chip_desc    = &pios_flash_chip_external,
		.first_sector = 0,
		.last_sector  = 5,
		.chip_offset  = 0,
		.size         = (5 - 0 + 1) * FLASH_SECTOR_64KB,
	},

	{
		.label        = FLASH_PARTITION_LABEL_AUTOTUNE,
		.chip_desc    = &pios_flash_chip_external,
		.first_sector = 6,
		.last_sector  = 10,
		.chip_offset  = (6 * FLASH_SECTOR_64KB),
		.size         = (10 - 6 + 1) * FLASH_SECTOR_64KB,
	},

	{
		.label        = FLASH_PARTITION_LABEL_LOG,
		.chip_desc    = &pios_flash_chip_external,
		.first_sector = 16,
		.last_sector  = 31,
		.chip_offset  = (16 * FLASH_SECTOR_64KB),
		.size         = (31 - 16 + 1) * FLASH_SECTOR_64KB,
	},
#endif	/* PIOS_INCLUDE_FLASH_JEDEC */
};

const struct pios_flash_partition * PIOS_BOARD_HW_DEFS_GetPartitionTable (uint32_t board_revision, uint32_t * num_partitions)
{
	PIOS_Assert(num_partitions);

	*num_partitions = NELEMENTS(pios_flash_partition_table);
	return pios_flash_partition_table;
}

#endif	/* PIOS_INCLUDE_FLASH */



#if defined(PIOS_INCLUDE_USART)

#include "pios_usart_priv.h"

#if defined(PIOS_INCLUDE_DSM)
/*
 * Spektrum/JR DSM USART
 */
#include <pios_dsm_priv.h>

static const struct pios_dsm_cfg pios_uart1_dsm_aux_cfg = {
	.bind = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin   = GPIO_Pin_7,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_OUT,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_NOPULL
		},
	},
};

static const struct pios_dsm_cfg pios_uart2_dsm_aux_cfg = {
	.bind = {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin   = GPIO_Pin_15,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_OUT,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_NOPULL
		},
	},
};

static const struct pios_dsm_cfg pios_uart3_dsm_aux_cfg = {
	.bind = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin   = GPIO_Pin_11,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_OUT,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_NOPULL
		},
	},
};

#endif	/* PIOS_INCLUDE_DSM */

static const struct pios_usart_cfg pios_uart1_cfg = {
	.regs = USART1,
	.remap = GPIO_AF_7,
	.irq = {
		.init = {
			.NVIC_IRQChannel                   = USART1_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGHEST,
			.NVIC_IRQChannelSubPriority        = 0,
			.NVIC_IRQChannelCmd                = ENABLE,
		  },
	},
	.rx = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin   = GPIO_Pin_7,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
		.pin_source = GPIO_PinSource7,
	},
	.tx = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin   = GPIO_Pin_6,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_DOWN
		},
		.pin_source = GPIO_PinSource6,
	},
};

static const struct pios_usart_cfg pios_uart2_cfg = {
	.regs = USART2,
	.remap = GPIO_AF_7,
	.irq = {
		.init = {
			.NVIC_IRQChannel = USART2_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGHEST,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.rx = {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin   = GPIO_Pin_15,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
		.pin_source = GPIO_PinSource15,
	},
	.tx = {
		.gpio = GPIOA,
		.init = {
			.GPIO_Pin   = GPIO_Pin_14,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_DOWN
		},
		.pin_source = GPIO_PinSource14,
	},
};

static const struct pios_usart_cfg pios_uart3_cfg = {
	.regs = USART3,
	.remap = GPIO_AF_7,
	.irq = {
		.init = {
			.NVIC_IRQChannel = USART3_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGHEST,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.rx = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin   = GPIO_Pin_11,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_UP
		},
		.pin_source = GPIO_PinSource11,
	},
	.tx = {
		.gpio = GPIOB,
		.init = {
			.GPIO_Pin   = GPIO_Pin_10,
			.GPIO_Speed = GPIO_Speed_2MHz,
			.GPIO_Mode  = GPIO_Mode_AF,
			.GPIO_OType = GPIO_OType_PP,
			.GPIO_PuPd  = GPIO_PuPd_DOWN
		},
		.pin_source = GPIO_PinSource10,
	},
};

#endif  /* PIOS_INCLUDE_USART */

#if defined(PIOS_INCLUDE_COM)

#include "pios_com_priv.h"

#endif	/* PIOS_INCLUDE_COM */

#if defined(PIOS_INCLUDE_RTC)
/*
 * Realtime Clock (RTC)
 */
#include <pios_rtc_priv.h>

void PIOS_RTC_IRQ_Handler (void);
void RTC_WKUP_IRQHandler() __attribute__ ((alias ("PIOS_RTC_IRQ_Handler")));
static const struct pios_rtc_cfg pios_rtc_main_cfg = {
	.clksrc = RCC_RTCCLKSource_HSE_Div32,
	.prescaler = 25 - 1, // 8MHz / 32 / 16 / 25 == 625Hz
	.irq = {
		.init = {
			.NVIC_IRQChannel                   = RTC_WKUP_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority        = 0,
			.NVIC_IRQChannelCmd                = ENABLE,
		},
	},
};

void PIOS_RTC_IRQ_Handler (void)
{
	PIOS_RTC_irq_handler ();
}

#endif

#include "pios_tim_priv.h"

static const TIM_TimeBaseInitTypeDef tim_8_time_base = {
	.TIM_Prescaler = (PIOS_PERIPHERAL_APB2_CLOCK / 1000000) - 1,
	.TIM_ClockDivision = TIM_CKD_DIV1,
	.TIM_CounterMode = TIM_CounterMode_Up,
	.TIM_Period = ((1000000 / PIOS_SERVO_UPDATE_HZ) - 1),
	.TIM_RepetitionCounter = 0x0000,
};

static const TIM_TimeBaseInitTypeDef tim_2_4_time_base = {
	.TIM_Prescaler = (PIOS_PERIPHERAL_APB1_CLOCK / 1000000 * 2) - 1,
	.TIM_ClockDivision = TIM_CKD_DIV1,
	.TIM_CounterMode = TIM_CounterMode_Up,
	.TIM_Period = ((1000000 / PIOS_SERVO_UPDATE_HZ) - 1),
	.TIM_RepetitionCounter = 0x0000,
};

/* Output Timers */
static const struct pios_tim_clock_cfg tim_2_cfg = {
	.timer = TIM2,
	.time_base_init = &tim_2_4_time_base,
	.irq = {
		.init = {
			.NVIC_IRQChannel                   = TIM2_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority        = 0,
			.NVIC_IRQChannelCmd                = ENABLE,
		},
	},
};
static const struct pios_tim_clock_cfg tim_4_cfg = {
	.timer = TIM4,
	.time_base_init = &tim_2_4_time_base,
	.irq = {
		.init = {
			.NVIC_IRQChannel                   = TIM4_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority        = 0,
			.NVIC_IRQChannelCmd                = ENABLE,
		},
	},
};
static const struct pios_tim_clock_cfg tim_8_cfg = {
	.timer = TIM8,
	.time_base_init = &tim_8_time_base,
	.irq = {
		.init = {
			.NVIC_IRQChannel                   = TIM8_CC_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
			.NVIC_IRQChannelSubPriority        = 0,
			.NVIC_IRQChannelCmd                = ENABLE,
		},
	},
};

/**
 * Pios servo configuration structures
 */
/*
 * 	OUTPUTS
	1:  TIM4_CH3 (PB8)
	2:  TIM8_CH3 (PB9)
	3:  TIM2_CH4 (PA3)
	4:  TIM2_CH3 (PA2)
 */
static const struct pios_tim_channel pios_tim_servoport_pins[] = {
		{ // Ch1
		.timer = TIM4,
		.timer_chan = TIM_Channel_3,
		.remap = GPIO_AF_2,
		.pin = {
			.gpio = GPIOB,
			.init = {
				.GPIO_Pin = GPIO_Pin_8,
				.GPIO_Speed = GPIO_Speed_2MHz,
				.GPIO_Mode  = GPIO_Mode_AF,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
			.pin_source = GPIO_PinSource8,
		},
	},
	{ // Ch2
		.timer = TIM8,
		.timer_chan = TIM_Channel_3,
		.remap = GPIO_AF_10,
		.pin = {
			.gpio = GPIOB,
			.init = {
				.GPIO_Pin = GPIO_Pin_9,
				.GPIO_Speed = GPIO_Speed_2MHz,
				.GPIO_Mode  = GPIO_Mode_AF,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
			.pin_source = GPIO_PinSource9,
		},
	},
		{ // Ch3
		.timer = TIM2,
		.timer_chan = TIM_Channel_4,
		.remap = GPIO_AF_1,
		.pin = {
			.gpio = GPIOA,
			.init = {
				.GPIO_Pin = GPIO_Pin_3,
				.GPIO_Speed = GPIO_Speed_2MHz,
				.GPIO_Mode  = GPIO_Mode_AF,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
			.pin_source = GPIO_PinSource3,
		},
	},
	{ // Ch4
		.timer = TIM2,
		.timer_chan = TIM_Channel_3,
		.remap = GPIO_AF_1,
		.pin = {
			.gpio = GPIOA,
			.init = {
				.GPIO_Pin = GPIO_Pin_2,
				.GPIO_Speed = GPIO_Speed_2MHz,
				.GPIO_Mode  = GPIO_Mode_AF,
				.GPIO_OType = GPIO_OType_PP,
				.GPIO_PuPd  = GPIO_PuPd_UP
			},
			.pin_source = GPIO_PinSource2,
		},
	},
};


#if defined(PIOS_INCLUDE_SERVO) && defined(PIOS_INCLUDE_TIM)
/*
 * Servo outputs
 */
#include <pios_servo_priv.h>

static const struct pios_servo_cfg pios_servo_cfg = {
	.tim_oc_init = {
		.TIM_OCMode = TIM_OCMode_PWM1,
		.TIM_OutputState = TIM_OutputState_Enable,
		.TIM_OutputNState = TIM_OutputNState_Disable,
		.TIM_Pulse = PIOS_SERVOS_INITIAL_POSITION,
		.TIM_OCPolarity = TIM_OCPolarity_High,
		.TIM_OCNPolarity = TIM_OCPolarity_High,
		.TIM_OCIdleState = TIM_OCIdleState_Reset,
		.TIM_OCNIdleState = TIM_OCNIdleState_Reset,
	},
	.channels = pios_tim_servoport_pins,
	.num_channels = NELEMENTS(pios_tim_servoport_pins),
};

#endif	/* PIOS_INCLUDE_SERVO && PIOS_INCLUDE_TIM */

#if defined(PIOS_INCLUDE_ADC)
#include "pios_adc_priv.h"
#include "pios_internal_adc_priv.h"

//-------------------------
// ADC
// ADC0 : PB0 ADC3_IN12 Curr
// ADC1 : PB1 ADC3_IN1 Vbat
//-------------------------

// board uses an ina139, RL=0.005, Rs=30000
// V/A = (0.005 * 0.001 * 30000) * I
#define TINYFISH_CURRENT_CALIBRATION_VALUE 15.0f // mV/A
#define TINYFISH_VOLTAGE_CALIBRATION_VALUE 63.69f // mV/V

static const struct pios_internal_adc_cfg internal_adc_cfg = {
	.dma = {
		.irq = {
			.flags   = (DMA2_FLAG_TC1 | DMA2_FLAG_TE1 | DMA2_FLAG_HT1 | DMA2_FLAG_GL1),
			.init    = {
				.NVIC_IRQChannel                   = DMA2_Channel1_IRQn,
				.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
				.NVIC_IRQChannelSubPriority        = 0,
				.NVIC_IRQChannelCmd                = ENABLE,
			},
		},
		.rx = {
			.channel = DMA2_Channel1,
			.init    = {
				.DMA_Priority           = DMA_Priority_High,
			},
		}
	},
	.half_flag = DMA2_IT_HT1,
	.full_flag = DMA2_IT_TC1,
	.oversampling = 32,
	.adc_pin_count = 2,
	.adc_pins = {
		{GPIOB,GPIO_Pin_0,ADC_Channel_12,true},
		{GPIOB,GPIO_Pin_1,ADC_Channel_1,true},
	},
	.adc_dev_master = ADC3,
	.adc_dev_slave = NULL,
};


#endif /* PIOS_INCLUDE_ADC */


#if defined(PIOS_INCLUDE_GCSRCVR)
#include "pios_gcsrcvr_priv.h"
#endif	/* PIOS_INCLUDE_GCSRCVR */


#if defined(PIOS_INCLUDE_RCVR)
#include "pios_rcvr_priv.h"
#endif /* PIOS_INCLUDE_RCVR */


#if defined(PIOS_INCLUDE_USB)
#include "pios_usb_priv.h"

static const struct pios_usb_cfg pios_usb_main_cfg = {
	.irq = {
		.init    = {
			.NVIC_IRQChannel                   = USB_LP_CAN1_RX0_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_LOW,
			.NVIC_IRQChannelSubPriority        = 0,
			.NVIC_IRQChannelCmd                = ENABLE,
		},
	},
	.vsense = {
		.gpio = NULL
	}
};

const struct pios_usb_cfg * PIOS_BOARD_HW_DEFS_GetUsbCfg (uint32_t board_revision)
{
	return &pios_usb_main_cfg;
}

#include "pios_usb_board_data_priv.h"
#include "pios_usb_desc_hid_cdc_priv.h"
#include "pios_usb_desc_hid_only_priv.h"
#include "pios_usbhook.h"

#endif	/* PIOS_INCLUDE_USB */

#if defined(PIOS_INCLUDE_COM_MSG)

#include <pios_com_msg_priv.h>

#endif /* PIOS_INCLUDE_COM_MSG */

#if defined(PIOS_INCLUDE_USB_HID)
#include <pios_usb_hid_priv.h>

const struct pios_usb_hid_cfg pios_usb_hid_cfg = {
	.data_if = 0,
	.data_rx_ep = 1,
	.data_tx_ep = 1,
};
#endif /* PIOS_INCLUDE_USB_HID */

#if defined(PIOS_INCLUDE_USB_CDC)
#include <pios_usb_cdc_priv.h>

const struct pios_usb_cdc_cfg pios_usb_cdc_cfg = {
	.ctrl_if = 1,
	.ctrl_tx_ep = 2,

	.data_if = 2,
	.data_rx_ep = 3,
	.data_tx_ep = 3,
};
#endif	/* PIOS_INCLUDE_USB_CDC */

/**
 * Configuration for the MPU6000 chip
 */
#if defined(PIOS_INCLUDE_MPU)
#include "pios_mpu.h"
static const struct pios_exti_cfg pios_exti_mpu_cfg __exti_config = {
	.vector = PIOS_MPU_IRQHandler,
	.line = EXTI_Line13,
	.pin = {
		.gpio = GPIOC,
		.init = {
			.GPIO_Pin = GPIO_Pin_13,
			.GPIO_Speed = GPIO_Speed_50MHz,
			.GPIO_Mode = GPIO_Mode_IN,
			.GPIO_OType = GPIO_OType_OD,
			.GPIO_PuPd = GPIO_PuPd_NOPULL,
		},
	},
	.irq = {
		.init = {
			.NVIC_IRQChannel = EXTI15_10_IRQn,
			.NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_HIGH,
			.NVIC_IRQChannelSubPriority = 0,
			.NVIC_IRQChannelCmd = ENABLE,
		},
	},
	.exti = {
		.init = {
			.EXTI_Line = EXTI_Line13, // matches above GPIO pin
			.EXTI_Mode = EXTI_Mode_Interrupt,
			.EXTI_Trigger = EXTI_Trigger_Rising,
			.EXTI_LineCmd = ENABLE,
		},
	},
};

static struct pios_mpu_cfg pios_mpu_cfg = {
	.exti_cfg = &pios_exti_mpu_cfg,
	.default_samplerate = 1000,
	.orientation = PIOS_MPU_BOTTOM_180DEG
};

#endif /* PIOS_INCLUDE_MPU */

/**
 * @}
 * @}
 */
