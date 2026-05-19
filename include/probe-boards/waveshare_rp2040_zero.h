/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PROBE_BOARDS_PICO_H
#define _PROBE_BOARDS_PICO_H

// required to set some paths
pico_board_cmake_set(PICO_PLATFORM, rp2040)

#include "boards/waveshare_rp2040_zero.h"

// --- Definitions for YAPicoprobe

// Base value of sys_clk in MHz.  Must be <=125MHz per RP2040 spec and a multiple of 24MHz
// to support integer divisors of the PIO clock and ADC clock (for sigrok).
// Can be overridden via configuration.
#ifdef OPT_MCU_FORCE_CLOCK_MHZ
    #define PROBE_CPU_CLOCK_MHZ  OPT_MCU_FORCE_CLOCK_MHZ
#else
    #define PROBE_CPU_CLOCK_MHZ  192
#endif
#define PROBE_CPU_CLOCK_MIN_MHZ  (5 * 24)
#define PROBE_CPU_CLOCK_MAX_MHZ  (12 * 24)

// Pin usage
//  - GP0 probe's debug uart output.
//  - GP1: SWDIR, GP2: SWCLK, GP3: SWDIO.
//  - GP4 and GP5 are target uart.
//  - GP6 is target reset.
//  - GP7 is reserved, I want to make it into a square wave output. For now it's a temporary status indicator.
//  - GP8-GP15 are digital inputs.
//  - GP16 is connected to the ws8212 led.
//  - GP17-25 are not part of the castellated pins.
//  - GP26-29 are ADC.
#undef PICO_DEFAULT_UART_RX_PIN // Disable stdin.

// LED config for programmable LED.
// #define PROBE_LED 7
#define PROBE_RGB_LED PICO_DEFAULT_WS2812_PIN
#define PROBE_RGB_LED_PIO pio0
#define PROBE_RGB_LED_PIO_SM 1

// PIO config
#define PROBE_PIO                pio0
#define PROBE_PIO_SM             0
#define PROBE_PIO_PIN_OFFSET     1
#define PROBE_PIO_PIN_COUNT      3
#define PROBE_PIO_PIN_SWDIR      (PROBE_PIO_PIN_OFFSET + 0)
#define PROBE_PIO_PIN_SWCLK      (PROBE_PIO_PIN_OFFSET + 1)
#define PROBE_PIO_PIN_SWDIO      (PROBE_PIO_PIN_OFFSET + 2)
#define PROBE_PIO_PIN_RESET      6                      // Target reset config
//#define PROBE_MAX_KHZ         now in g_board_info.target_cfg->rt_max_swd_kHz, setup in pico::pico_prerun_board_config()

// UART config (UART target -> probe)
#define PROBE_UART_TX            4
#define PROBE_UART_RX            5
#define PROBE_UART_INTERFACE     uart1
#define PROBE_UART_BAUDRATE      115200

// sigrok config
#define SIGROK_PIO               pio1
#define SIGROK_SM                0                      // often hard coded

// number of analog channels
#define SR_NUM_A_CHAN            4
// first digital channel port
#define SR_BASE_D_CHAN           8
// number of digital channels
#define SR_NUM_D_CHAN            8
// Storage size of the DMA buffer.  The buffer is split into two halves so that when the first
// buffer fills we can send the trace data serially while the other buffer is DMA'd into.
// 102000 buffer size allows 200000 of D4 samples.
#define SR_DMA_BUF_SIZE          102000


#endif
