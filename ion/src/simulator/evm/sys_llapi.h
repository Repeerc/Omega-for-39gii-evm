#ifndef __SYS_LLAPI_H__
#define __SYS_LLAPI_H__

#include <stdint.h>
#include <stdbool.h>

#include "llapi_code.h"

#ifndef NAKED
#define NAKED   __attribute__((naked))
#endif

#ifdef __cplusplus
    extern "C" {
#endif


void ll_putChr(char c);
void ll_putStr(char *s);
void ll_delay(uint32_t ms);
uint32_t ll_gettime_us(void);
void ll_putStr2(char *s, uint32_t len);


uint32_t ll_DispFlush(DispFlushInfo_t *s);

uint32_t NAKED ll_vm_check_key(void);
void NAKED ll_vmsleep_ms(uint32_t ms);
void  ll_setKeyboard(bool enable_report);
void ll_setTimer(bool enbale, uint32_t period_ms);
void ll_set_irq_vector(uint32_t addr);
void ll_set_irq_stack(uint32_t addr);
void ll_set_svc_stack(uint32_t addr) __attribute__((naked));
void ll_set_svc_vector(uint32_t addr) __attribute__((naked));
void ll_set_context(uint32_t addr) __attribute__((naked));
void ll_get_context(uint32_t addr);
void ll_restore_context(uint32_t addr) __attribute__((naked));
void ll_enable_irq(bool enable);




 
void ll_DispPutStr(char *s, uint32_t x0, uint32_t y0, uint8_t fg, uint8_t bg, uint8_t fontsize);
void ll_DispPutBox(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, bool fill, uint8_t color);

void ll_DispHLine(uint32_t y, uint32_t x0, uint32_t x1, uint32_t color);
void ll_DispVLine(uint32_t x, uint32_t y0, uint32_t y1, uint32_t color);

void NAKED ll_DispPutArea(uint8_t *vbuffer, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1);
void ll_DispSetIndicate(uint32_t indicateBit, uint8_t BatInt);
void ll_DispSendScreen(void);


uint32_t ll_taskCreate(uint32_t stack, void *entry);
void ll_taskEnterCritical(void);
void ll_taskExitCritical(void);
void ll_taskSleepUs(int64_t us);


#ifdef __cplusplus          
    }          
#endif

#endif