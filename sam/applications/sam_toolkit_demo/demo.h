/**
 * \file
 *
 * \brief Main header file for SAM toolkit demo.
 *
 * Copyright (c) 2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

#ifndef DEMO_H_INCLUDED
#define DEMO_H_INCLUDED

#include "demo_parameters.h"
#include "conf_board.h"
#include "conf_demo.h"

#define DEMO_QTOUCH

/* For ADC input frame */
#define NB_VAL 256
#define FFT_IN_GAIN  3
#define FFT_OUT_GAIN 30
/* Max display FREQ */
#define MAX_FFT_DISP_FREQ 20000
/* 128K, 128 sample/ms */
#define AUDIO_SAMPLE_RATE 256000
/* 128 samples */
#define AUDIO_FRAME_SIZE (AUDIO_SAMPLE_RATE/1000)
/* Number of frame buffer */
#define AUDIO_NB_BUFFER ((NB_VAL/AUDIO_FRAME_SIZE)+3)
/* Total frame buffer size, in samples */
#define AUDIO_BUFFER_SIZE (AUDIO_NB_BUFFER*AUDIO_FRAME_SIZE)
#define SYSTICK_FREQ 1000

/**
 * \brief Special window mode ID.
 */
typedef enum demo_special_mode_id {
	/** ID for qtouch mode */
	DEMO_QTOUCH_MODE = 0,
	/** ID for lcd calibration mode */
	DEMO_LCD_CALIBRATE_MODE,
	/** ID for PPT mode */
	DEMO_PPT_MODE,
	/** ID for wait mode */
	DEMO_WAIT_MODE,
	/** ID for sleep mode */
	DEMO_SLEEP_MODE,
	/** ID for main mode */
	DEMO_MAIN_MODE,
	/** ID for main mode */
	DEMO_FFT_MODE,
	/** Max special mode */
	DEMO_SPEC_MODE_MAX
}demo_special_mode_id;

/** Demo board name */
extern char demo_board_name[];

void app_widget_main_on(uint8_t on);
void app_widget_settings_on(uint8_t on);
void app_widget_settings_time_on(uint8_t on);
void app_widget_settings_date_on(uint8_t on);
void app_widget_settings_backlight_on(uint8_t on);
void app_widget_settings_tsd_on(uint8_t on);
void app_widget_lpm_on(uint8_t on);
void app_widget_lpm_wait_on(uint8_t on);
void app_widget_lpm_backup_on(uint8_t on);
void app_widget_lpm_sleep_on(uint8_t on);
void app_widget_qtouch_on(uint8_t on);
void app_widget_info_on(uint8_t on);
void set_widget_ppt_mode( void );
void app_widget_audio_on(uint8_t on);
void app_widget_fft_on(void);
void demo_set_special_mode_status( demo_special_mode_id id, uint8_t status );
uint8_t demo_get_special_mode_status( demo_special_mode_id id );
void demo_qt_init(void);
void demo_qtouch_event_handler( void );
uint8_t demo_draw_bmpfile_init(void);

#endif /* DEMO_H_INCLUDED */
