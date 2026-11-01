#Running environment variable file before Makefile

BRDIR=/media/amaan/work/EMBLOGIC/rpi/Rasberry_pi
KDIR=/media/amaan/work/EMBLOGIC/rpi/Rasberry_pi/build/linux-custom

PWD=$(shell pwd)

obj-m=pl011_uart.o
pl011_uart-objs += uart_init.o uart_exit.o uart_open.o uart_close.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
