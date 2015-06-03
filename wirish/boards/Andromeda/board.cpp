/******************************************************************************
 * The MIT License
 *
 * Copyright
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file   wirish/boards/Andromeda/board.cpp
 * @author Schumy Hao <schumy@wrtnode.com>
 * @brief  Andromeda board file.
 */

#include <board/board.h>         // For this board's header file

#include <wirish/wirish_types.h> // For stm32_pin_info and its contents
                                 // (these go into PIN_MAP).

#include "boards_private.h"      // For PMAP_ROW(), which makes
                                 // PIN_MAP easier to read.

// boardInit(): nothing special to do for Maple.
//
// When defining your own board.cpp, you can put extra code in this
// function if you have anything you want done on reset, before main()
// or setup() are called.
//
// If there's nothing special you need done, feel free to leave this
// function out, as we do here.
/*
void boardInit(void) {
}
*/

// Pin map: this lets the basic I/O functions (digitalWrite(),
// analogRead(), pwmWrite()) translate from pin numbers to STM32
// peripherals.
//
// PMAP_ROW() lets us specify a row (really a struct stm32_pin_info)
// in the pin map. Its arguments are:
//
// - GPIO device for the pin (GPIOA, etc.)
// - GPIO bit for the pin (0 through 15)
// - Timer device, or NULL if none
// - Timer channel (1 to 4, for PWM), or 0 if none
// - ADC device, or NULL if none
// - ADC channel, or ADCx if none
extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {

    PMAP_ROW(GPIOA,  10, TIMER1,  3, NULL, ADCx), /* D0/PA10 */
    PMAP_ROW(GPIOA,   9, TIMER1,  2, NULL, ADCx), /* D1/PA9 */
    PMAP_ROW(GPIOB,  11, TIMER2,  4, NULL, ADCx), /* D2/PB11 */
    PMAP_ROW(GPIOB,  10, TIMER2,  3, NULL, ADCx), /* D3/PB10 */
    PMAP_ROW(GPIOA,   5,   NULL,  0, ADC1,    5), /* D4/PA5 */
    PMAP_ROW(GPIOA,   6, TIMER3,  1, ADC1,    6), /* D5/PA6 */
    PMAP_ROW(GPIOA,   7, TIMER3,  2, ADC1,    7), /* D6/PA7 */
    PMAP_ROW(GPIOB,   0, TIMER3,  3, ADC1,    8), /* D7/PB0 */
    PMAP_ROW(GPIOB,   6, TIMER4,  1, NULL, ADCx), /* D8/PB6 */
    PMAP_ROW(GPIOB,   7, TIMER4,  2, NULL, ADCx), /* D9/PB7 */
    PMAP_ROW(GPIOB,   8, TIMER4,  3, NULL, ADCx), /* D10/PB8 */
    PMAP_ROW(GPIOB,   9, TIMER4,  4, NULL, ADCx), /* D11/PB9 */
    PMAP_ROW(GPIOB,  12,   NULL,  0, NULL, ADCx), /* D12/PB12 */
    PMAP_ROW(GPIOB,   1, TIMER3,  4, ADC1,    9), /* D13/PB1(LED) */

    PMAP_ROW(GPIOA,   0, TIMER2,  1, ADC1,    0), /* D14/PA0 */
    PMAP_ROW(GPIOA,   1, TIMER2,  2, ADC1,    1), /* D15/PA1 */
    PMAP_ROW(GPIOA,   2, TIMER2,  3, ADC1,    2), /* D16/PA2 */
    PMAP_ROW(GPIOA,   3, TIMER2,  4, ADC1,    3), /* D17/PA3 */
    PMAP_ROW(GPIOA,   4,   NULL,  0, ADC1,    4), /* D18/PA4 */
    
    PMAP_ROW(GPIOA,  13,   NULL,  0, NULL, ADCx), /* D19/PA13 */
    PMAP_ROW(GPIOA,  14,   NULL,  0, NULL, ADCx), /* D20/PA14 */
    PMAP_ROW(GPIOA,  15,   NULL,  0, NULL, ADCx), /* D21/PA15 */
    PMAP_ROW(GPIOB,   3,   NULL,  0, NULL, ADCx), /* D22/PB3 */
    PMAP_ROW(GPIOB,   4,   NULL,  0, NULL, ADCx), /* D23/PB4 */
};

// Array of pins you can use for pwmWrite(). Keep it in Flash because
// it doesn't change, and so we don't waste RAM.
extern const uint8 boardPWMPins[] __FLASH__ = {
    0, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17
};

// Array of pins you can use for analogRead().
extern const uint8 boardADCPins[] __FLASH__ = {
    4, 5, 6, 7, 13, 14, 15, 16, 17, 18
};

// Array of pins that the board uses for something special. Other than
// the button and the LED, it's usually best to leave these pins alone
// unless you know what you're doing.
extern const uint8 boardUsedPins[] __FLASH__ = {
    BOARD_LED_PIN, BOARD_JTMS_SWDIO_PIN,
    BOARD_JTCK_SWCLK_PIN, BOARD_JTDI_PIN, BOARD_JTDO_PIN, BOARD_NJTRST_PIN
};
