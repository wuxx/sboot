#ifndef __PLATFORM_RPI_B_H__
#define __PLATFORM_RPI_B_H__

/* CPSR bit */
#define FIQ_DISABLE_BIT 6
#define IRQ_DISABLE_BIT 7

enum IRQ_NR_E {
    /* arm basic irq */
    IRQ_CORE_TIMER     = 0,
    IRQ_CORE_MAILBOX   = 1,
    IRQ_CORE_DOORBELL0 = 2,
    IRQ_CORE_DOORBELL1 = 3,
    IRQ_GPU0_HALT      = 4,
    IRQ_GPU1_HALT      = 5,
    IRQ_ILEGAL_ACCESS0 = 6,
    IRQ_ILEGAL_ACCESS1 = 7,

    /* arm peripherals irq */
    IRQ_SYS_TIMER0  = 32 +  0,  
    IRQ_SYS_TIMER1  = 32 +  1,  
    IRQ_SYS_TIMER2  = 32 +  2,  
    IRQ_SYS_TIMER3  = 32 +  3,  
    IRQ_AUX         = 32 + 29, 
    IRQ_I2C_SPI_SLV = 32 + 43, 
    IRQ_SMI         = 32 + 48, 
    IRQ_GPIO0       = 32 + 49, 
    IRQ_GPIO1       = 32 + 50, 
    IRQ_GPIO2       = 32 + 51, 
    IRQ_GPIO3       = 32 + 52, 
    IRQ_I2C         = 32 + 53, 
    IRQ_SPI         = 32 + 54, 
    IRQ_PCM         = 32 + 55, 
    IRQ_UART        = 32 + 57, 
    IRQ_MAX         = 32 * 3,
};

enum {

    /* peripherals */
    SYSTIMER_BASE = 0x20003000,
        SYSTMCS  = (SYSTIMER_BASE + 0x00),
        SYSTMCLO = (SYSTIMER_BASE + 0x04),
        SYSTMCHI = (SYSTIMER_BASE + 0x08),
        SYSTMC0  = (SYSTIMER_BASE + 0x0C),
        SYSTMC1  = (SYSTIMER_BASE + 0x10),
        SYSTMC2  = (SYSTIMER_BASE + 0x14),
        SYSTMC3  = (SYSTIMER_BASE + 0x18),

    IRQ_BASE = 0x2000B200,
        IRQ_PEND_BASIC    = (IRQ_BASE + 0x00),
        IRQ_PEND1         = (IRQ_BASE + 0x04),
        IRQ_PEND2         = (IRQ_BASE + 0x08),
        FIQ_CTRL          = (IRQ_BASE + 0x0C),
        IRQ_ENABLE1       = (IRQ_BASE + 0x10),
        IRQ_ENABLE2       = (IRQ_BASE + 0x14),
        IRQ_ENABLE_BASIC  = (IRQ_BASE + 0x18),
        IRQ_DISABLE1      = (IRQ_BASE + 0x1C),
        IRQ_DISABLE2      = (IRQ_BASE + 0x20),
        IRQ_DISABLE_BASIC = (IRQ_BASE + 0x24),

    CORETIMER_BASE = 0x2000B400,
        CORETMLOAD  = (CORETIMER_BASE + 0x00),
        CORETMVAL   = (CORETIMER_BASE + 0x04),
        CORETMCTRL  = (CORETIMER_BASE + 0x08),
        CORETMCLR   = (CORETIMER_BASE + 0x0C),
        CORETMRAW   = (CORETIMER_BASE + 0x10),
        CORETMMSK   = (CORETIMER_BASE + 0x14),
        CORETMRELD  = (CORETIMER_BASE + 0x18),
        CORETMPRED  = (CORETIMER_BASE + 0x1C),
        CORETMFRC   = (CORETIMER_BASE + 0x20),

    WATCHDOG_BASE = 0x20100000,
        WATCHDOG_RSTC = (WATCHDOG_BASE + 0x1C),
        WATCHDOG_WDOG = (WATCHDOG_BASE + 0x24),

    GPIO_BASE = 0x20200000,
        GPFSEL0 = (GPIO_BASE + 0x00),
        GPFSEL1 = (GPIO_BASE + 0x04),
        GPFSEL2 = (GPIO_BASE + 0x08),
        GPFSEL3 = (GPIO_BASE + 0x0C),
        GPFSEL4 = (GPIO_BASE + 0x10),
        GPFSEL5 = (GPIO_BASE + 0x14),

        GPSET0  = (GPIO_BASE + 0x1C),
        GPSET1  = (GPIO_BASE + 0x20),

        GPCLR0  = (GPIO_BASE + 0x28),
        GPCLR1  = (GPIO_BASE + 0x2C),

        GPLEV0  = (GPIO_BASE + 0x34),
        GPLEV1  = (GPIO_BASE + 0x38),

        GPEDS0  = (GPIO_BASE + 0x40),
        GPEDS1  = (GPIO_BASE + 0x44),

        GPREN0  = (GPIO_BASE + 0x4C),
        GPREN1  = (GPIO_BASE + 0x50),

        GPFEN0  = (GPIO_BASE + 0x58),
        GPFEN1  = (GPIO_BASE + 0x5C),

        GPHEN0  = (GPIO_BASE + 0x64),
        GPHEN1  = (GPIO_BASE + 0x68),

        GPLEN0  = (GPIO_BASE + 0x70),
        GPLEN1  = (GPIO_BASE + 0x74),

        GPAREN0 = (GPIO_BASE + 0x7C),
        GPAREN1 = (GPIO_BASE + 0x80),

        GPAFEN0 = (GPIO_BASE + 0x88),
        GPAFEN1 = (GPIO_BASE + 0x8C),

        GPPUD   = (GPIO_BASE + 0x94),

        GPPUDCLK0 = (GPIO_BASE + 0x98),
        GPPUDCLK1 = (GPIO_BASE + 0x9C),

    UART0_BASE = 0x20201000,
        UART0_DR     = (UART0_BASE + 0x00),
        UART0_RSRECR = (UART0_BASE + 0x04),
        UART0_FR     = (UART0_BASE + 0x18),
        UART0_ILPR   = (UART0_BASE + 0x20),
        UART0_IBRD   = (UART0_BASE + 0x24),
        UART0_FBRD   = (UART0_BASE + 0x28),
        UART0_LCRH   = (UART0_BASE + 0x2C),
        UART0_CR     = (UART0_BASE + 0x30),
        UART0_IFLS   = (UART0_BASE + 0x34),
        UART0_IMSC   = (UART0_BASE + 0x38),
        UART0_RIS    = (UART0_BASE + 0x3C),
        UART0_MIS    = (UART0_BASE + 0x40),
        UART0_ICR    = (UART0_BASE + 0x44),
        UART0_DMACR  = (UART0_BASE + 0x48),
        UART0_ITCR   = (UART0_BASE + 0x80),
        UART0_ITIP   = (UART0_BASE + 0x84),
        UART0_ITOP   = (UART0_BASE + 0x88),
        UART0_TDR    = (UART0_BASE + 0x8C),
};

#endif /* __PLATFORM_RPI_B_H__ */
