#include <platform_rpi_b.h>
#include <libc.h>
#include <mmio.h>
#include "uart.h"

char sys_banner[] = {"sboot system buildtime [" __TIME__ " " __DATE__ "]"};

extern u32 __get_cpsr();

void lock_irq()
{
    u32 _cpsr = __get_cpsr();

    set_bit(&_cpsr, IRQ_DISABLE_BIT, 1); 
    asm volatile("msr CPSR_c, %[_cpsr]"
            :   
            : [_cpsr]"r"(_cpsr));
}

void unlock_irq()
{
    u32 _cpsr = __get_cpsr();

    set_bit(&_cpsr, IRQ_DISABLE_BIT, 0);
    asm volatile("msr CPSR_c, %[_cpsr]"
            :
            : [_cpsr]"r"(_cpsr));
}

void ExcHandler()
{
    uart_printf("in %s \n", __func__);
    while(1);
}

void IrqHandler()
{
    uart_printf("in %s \n", __func__);
    while(1);
}


int main()
{
    lock_irq();    
    uart_init();
    uart_printf("%s\n", sys_banner);
    while(1) {
        uart_handler();
    }

    return 0;
}
