
#include <stdint.h>
#include "sys_llapi.h"
#include <stddef.h>




/* C++ expects the __dso_handle symbol to be defined to some unique value in
 * each dynamic shared object. Even though we're not using dynamic loading,
 * we still have to define __dso_handle. */

void *__dso_handle = NULL;

/* The __cxa_atexit function registers a function to be called when the program
 * exits or when a shared library is unloaded.
 * We don't support shared libraries and our program should never exit, so we
 * can simply do nothing and return zero. */

int __cxa_atexit(void (*dtor)(void *), void *object, void *handle)
{
    return 0;
}



extern const uint32_t data_load_start;
extern const uint32_t data_size;
extern const uint32_t data_start;

typedef void (*pfunc)();
extern pfunc __ctors_start__[];
extern pfunc __ctors_end__[];

extern const uint32_t _eronly;    /* End+1 of read only section (.text + .rodata) */
extern uint32_t _sdata;           /* Start of .data */
extern uint32_t _edata;           /* End+1 of .data */
extern uint32_t _sbss;
extern uint32_t _ebss;


int cpp_main(int argc, char *argv[]);



uint32_t key;
bool key_press;

uint32_t IRQ_Context[17];
uint32_t IRQ_Stack[400];


void __IRQ_ISR(uint32_t IRQNum, uint32_t par1, uint32_t par2, uint32_t par3)   __attribute__((naked));
 void __IRQ_ISR(uint32_t IRQNum, uint32_t par1, uint32_t par2, uint32_t par3)
{
  ll_get_context((uint32_t)IRQ_Context);
  
  if(IRQNum == LL_IRQ_KEYBOARD)
  {
    
    ll_putStr("KEY\n");
    key = par1;
    key_press = par2;
  
  }
  ll_putStr("IRQ\n");
  //printf("irq:%d, par1:%d, par2:%d, par3:%d\n",IRQNum, par1, par2, par3);

  ll_restore_context((uint32_t)IRQ_Context);
  while(1);

}

void  ___init() __attribute__((section(".init"))) __attribute__((naked));
void  ___init(void)
{
    const uint32_t *src;
    uint32_t *dest;
    
    // unsigned int size = ((unsigned int)&data_size);

    // for (unsigned int i = 0; i < size; i++)

    for (dest = &_sbss; dest < &_ebss; )
    {
      *dest++ = 0;
    }

    ll_putStr("Start copy data.\n");

    for (src = &_eronly, dest = &_sdata; dest < &_edata; )
    {
      *dest++ = *src++;

    }

 


    ll_putStr("Start ctor.\n");

    pfunc *p;
    for (p = __ctors_start__; p < __ctors_end__; p++)
    {
        (*p)();
    }

    ll_putStr("Start cpp_main.\n");

    ll_set_irq_stack((uint32_t)&IRQ_Stack[380]);
    ll_set_irq_vector((uint32_t)__IRQ_ISR);
    
    //ll_enable_irq(true);


    
    cpp_main(0, NULL);

    while (1)
        ;
}
