/* mbed Microcontroller Library
 * Copyright (c) 2006-2018 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "us_ticker_api.h"
#include "mbed_wait_api.h"
#include "emscripten.h"

void us_ticker_init(void)
{
    EM_ASM_({
        window.MbedJSHal.usticker.init();
    });
}

uint32_t us_ticker_read()
{
    return EM_ASM_INT({
        return window.MbedJSHal.usticker.read();
    });
}

void us_ticker_set_interrupt(timestamp_t timestamp)
{
    EM_ASM_({
        window.MbedJSHal.usticker.setInterrupt($0);
    }, (uint32_t)timestamp);
}

void us_ticker_disable_interrupt(void)
{
    EM_ASM({
        window.MbedJSHal.usticker.disableInterrupt();
    });
}

void us_ticker_fire_interrupt(void)
{
    EM_ASM({
        window.MbedJSHal.usticker.fireInterrupt();
    });
}

void us_ticker_clear_interrupt(void)
{
    EM_ASM({
        window.MbedJSHal.usticker.clearInterrupt();
    });
}

void us_ticker_free(void)
{
    EM_ASM({
        window.MbedJSHal.usticker.free();
    });
}

EMSCRIPTEN_KEEPALIVE
void handle_usticker_interrupt(void)
{
    us_ticker_irq_handler();
}
