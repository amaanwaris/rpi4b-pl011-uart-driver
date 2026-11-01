#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/atomic.h>
#include <linux/io.h>
#include <linux/device.h>
#include <linux/fs.h>

#ifndef DEBUG
#define DEBUG

#ifndef DEVICE_NAME
#define DEVICE_NAME "p111_uart_rspie"
#endif

#ifndef MAJORNUMBER
#define MAJORNUMBER 0
#endif

#ifndef MINORNUMBER
#define MINORNUMBER 0
#endif

#ifndef NOD
#define NOD 1
#endif

#ifndef UART_BASE
#define UART_BASE 0xFE201A00
#endif

#ifndef UART_SIZE
#define UART_SIZE 0x1000
#endif

#ifndef UART_DR
#define UART_DR 0x00
#endif

#ifndef UART_FR
#define UART_FR 0x18      //flag register most important register of pl011 uart it is 32 bit register
#endif

#ifndef UART_IBRD
#define UART_IBRD 0x24  // Integer Baud Rate Divisor
#endif

#ifndef UART_FBRD
#define UART_FBDR 0x28  //Fractional Baud Rate Divisor
#endif

#ifndef UART_LCRH
#define UART_LCRH 0x2C  //Line Control Register
#endif

#ifndef UART_CR
#define UART_CR 0x30   //Control Register
#endif

#ifndef UART_IMSC
#define UART_IMSC 0x38  //Interrupt Mask set /clear Register
#endif

#ifndef UART_MIS
#define UART_MIS 0x40   //Masked Interrupt Status Register
#endif

#ifndef UART_ICR
#define UART_ICR  0x44   //Interrupt clear Register
#endif

//uart flag (in the flag register)
#define UART_FR_TXFF (1 << 5) //tranmit fifo full
#define UART_FR_RXFE (1 << 4) //Recieve fifo empty

#ifndef GPIO_BASE
#define GPIO_BASE 0xFE200000  //Gpio controller base address in RPI4b BCM2711
#endif

#ifndef GPIO_SIZE
#define GPIO_SIZE 0x1000 //4kb
#endif

#ifndef GPFSEL1
#define GPFSEL1 0x04
#endif

#endif
