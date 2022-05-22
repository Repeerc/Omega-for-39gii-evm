

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "llapi_code.h"
#include "sys_llapi.h"

#ifdef __cplusplus
    extern "C" {
#endif

 void ll_putStr(char *s) __attribute__((naked));
 void ll_putStr(char *s)
{
    /*
    register uint32_t r0 asm("r0") = (uint32_t)s;
    __asm volatile (
    "swi %[num]" 
        : "=r"(r0)
        : [num] "i"(LL_SWI_WRITE_STRING1), 
            "r"(r0)
        : "memory", "r1", "r2", "r3", "r12", "lr"
    ); */
    
    __asm volatile("push {r0-r12}");
    __asm volatile("swi %0" :: "i"(LL_SWI_WRITE_STRING1));
    __asm volatile("pop {r0-r12}");
    __asm volatile("bx lr");

}

 void ll_putStr2(char *s, uint32_t len) __attribute__((naked));
 void ll_putStr2(char *s, uint32_t len)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_WRITE_STRING2));
    __asm volatile("bx lr");

}

 void ll_putChr(char c) __attribute__((naked));
 void ll_putChr(char c)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_PUT_CH));
    __asm volatile("bx lr");

    
}

 uint32_t ll_gettime_us()  __attribute__((naked));
 uint32_t ll_gettime_us()
{
    __asm volatile("swi %0" :: "i"(LL_SWI_GET_TIME_US));
    __asm volatile("bx lr");
}

void NAKED ll_vmsleep_ms(uint32_t ms)
{
    __asm volatile("push {r1-r12, lr}");
    __asm volatile("swi %0" :: "i"(LL_SWI_VM_SLEEP_MS));
    __asm volatile("pop {r1-r12, lr}");
    __asm volatile("bx lr");
}

uint32_t NAKED ll_vm_check_key(void)
{
    __asm volatile("swi %[num]" :: [num]"i"(LL_SWI_CHECK_KEY));
    __asm volatile("bx lr");
}

void ll_setTimer(bool enbale, uint32_t period_ms) __attribute__((naked));
void ll_setTimer(bool enbale, uint32_t period_ms)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_ENABLE_TIMER));
    __asm volatile("bx lr");
}



void ll_set_irq_vector(uint32_t addr) __attribute__((naked));
void ll_set_irq_vector(uint32_t addr)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_SET_IRQ_VECTOR));
    __asm volatile("bx lr");
}


void ll_set_irq_stack(uint32_t addr) __attribute__((naked));
void ll_set_irq_stack(uint32_t addr)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_SET_IRQ_STACK));
    __asm volatile("bx lr");
}

void ll_set_svc_vector(uint32_t addr) __attribute__((naked));
void ll_set_svc_vector(uint32_t addr)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_SET_SVC_VECTOR));
    __asm volatile("bx lr");
}


void ll_set_svc_stack(uint32_t addr) __attribute__((naked));
void ll_set_svc_stack(uint32_t addr)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_SET_SVC_STACK));
    __asm volatile("bx lr");
}

void ll_set_context(uint32_t addr) __attribute__((naked));
void ll_set_context(uint32_t addr)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_SET_CONTEXT));
}

void ll_restore_context(uint32_t addr) __attribute__((naked));
void ll_restore_context(uint32_t addr)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_RESTORE_CONTEXT));
}

//void ll_get_context(uint32_t addr) __attribute__((naked));
void ll_get_context(uint32_t addr)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_GET_CONTEXT));
}



//void ll_enable_irq(bool enable) __attribute__((naked));
void ll_enable_irq(bool enable)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_ENABLE_IRQ));
}




void NAKED ll_DispPutArea(uint8_t *vbuffer, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) 
{
    __asm volatile("swi %0" :: "i"(LL_SWI_DISPLAY_FLUSH));
    __asm volatile("bx lr");
}

// void ll_DispPutStr(char *s, uint32_t x0, uint32_t y0, uint8_t fg, uint8_t bg, uint8_t fontsize)
// {

//     register DispPutStrInfo_t *info;

//     info = malloc(sizeof(DispPutStrInfo_t));
//     info->string = s;
//     info->x0 = x0;
//     info->y0 = y0;
//     info->fg = fg;
//     info->bg = bg;
//     info->fontsize = fontsize;
    
//     __asm volatile (
//     "swi %[num]" 
//         : "=r"(info)
//         : [num] "i"(LL_SWI_DISPLAY_PUTSTR), 
//             "r"(info)
//         : "memory", "r1", "r2", "r3", "r12", "lr"
//     );

//     free(info);
// }


void ll_DispPutBox(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, bool fill, uint8_t color)
{

    register DispPutBoxInfo_t *info;

    info = malloc(sizeof(DispPutBoxInfo_t));
    info->color = color;
    info->x0 = x0;
    info->x1 = x1;
    info->y0 = y0;
    info->y1 = y1;
    info->fill = fill;
    
    __asm volatile (
    "swi %[num]" 
        : "=r"(info)
        : [num] "i"(LL_SWI_DISPLAY_PUT_BOX), 
            "r"(info)
        : "memory", "r1", "r2", "r3", "r12", "lr"
    );

    free(info);
}

void ll_DispHLine(uint32_t y, uint32_t x0, uint32_t x1, uint32_t color)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_DISPLAY_HLINE));
}

void ll_DispVLine(uint32_t x, uint32_t y0, uint32_t y1, uint32_t color)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_DISPLAY_VLINE));
}


void ll_DispSetIndicate(uint32_t indicateBit, uint8_t BatInt)
{
    __asm volatile("swi %0" :: "i"(LL_SWI_DISPLAY_SET_INDICATION));
}

#ifdef __cplusplus          
    }          
#endif

