/**
 * \file
 *
 * \brief Task configurations.
 *
 * Copyright (c) 2014 Atmel Corporation. All rights reserved.
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

#ifndef CONF_EXAMPLE_H
#define CONF_EXAMPLE_H

#define BOARD_UART  UART0
#define BOARD_USART  USART

/* Comment/Uncomment the following definitions to enable/disable to corresponding tasks. */
/* Note: only the listed tasks have hardware support. */

#define confINCLUDE_UART_CLI
#define confINCLUDE_USART_ECHO_TASKS
//#define confINCLUDE_USART_CLI
//#define confINCLUDE_CDC_CLI
//#define confINCLUDE_TWI_EEPROM_TASK
//#define confINCLUDE_SPI_FLASH_TASK

/* Less user LEDS are available on this kit, so redefine the corresponding define. */
#define partestNUM_LEDS                 (1UL)

/* No LED1 and LED2 available for this board. Junk values. */
#define LED1_GPIO						(0UL)
#define LED1_ACTIVE_LEVEL				(0UL)
#define LED2_GPIO						(0UL)
#define LED2_ACTIVE_LEVEL				(0UL)

#endif/* CONF_EXAMPLE_H */
