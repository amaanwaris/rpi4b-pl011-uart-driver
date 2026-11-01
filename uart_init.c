#include"header.h"
#include"declaration.h"
#include"fileoperation.h"

dev_t dev;
int majorno,minorno,nod;
Serialdev serialdev;
struct class *pl011_uart_class;
struct device *pl011_uart_device;
void __iomem *uart_base_addr;
void __iomem *gpio_base_addr;  


static void config_gpio_uart5(void)
{
    	// this function is required because i removed the device tree overlay for uart5 to stop
    	// uart5 to use pl011 alreday available driver so we need to configure uart5 gpio pin
    	// manualy, pin 12 and 13 is used for uart5.

    	u32 val, ret;

    	gpio_base_addr = ioremap(GPIO_BASE, GPIO_SIZE);
    	if (!gpio_base_addr)
    	{
        	pr_err("GPIO ioremap failed\n");
        	return;
    	}

#ifdef DEBUG
    	printk(KERN_INFO "pl011_uart:GPIO ioremap success at address %p\n",gpio_base_addr);
#endif

    	val = readl(gpio_base_addr + GPFSEL1); // GPFSEL1 is the register to controll gpio 10 to 19 in gpio controller

#ifdef DEBUG
    	printk(KERN_INFO "pl011_uart:GPFSEL1 befor = 0x%x\n", val);
#endif

    	val &= ~(0x07 << 6);   // clear bit number 6,7,8 for gpio 12 of reg GPFSEL1
    	val &= ~(0x07 << 9);   // clear bit number 9,10,11 for gpio 13 of reg GPFSEL1

	val |= (0x03 << 6);    // set bit 6,7,8 AS ALT4(011) in reg GPFSEL1
	val |= (0x03 << 9);    // set bit 9,10,11 as ALT4(011) in reg GPFSEL1

	writel(val, gpio_base_addr + GPFSEL1);   // write new setting of pin 12,13 in register GPFSEL1
	ret = readl(gpio_base_addr + GPFSEL1);   // read after write to verify write

#ifdef DEBUG
	printk(KERN_INFO "pl011_uart:GPFSEL1 after = 0x%x\n", ret);
#endif
}

static int __init uart_init(void )
{
                int ret;
#ifndef DEBUG
                pr_info("%s:Begin\n",__func__);
#endif
        	u32 fr;                                                                                                
		majorno =MAJORNUMBER;
                minorno =MINORNUMBER;
                nod=NOD;

                ret=alloc_chrdev_region(&dev , majorno , nod ,DEVICE_NAME);
                if(ret < 0)
                {
                                pr_info("%s : failed at alloc chrdev region\n",__func__);
                                goto err_unregister_chrdev;
                }
        majorno=MAJOR(dev);
                minorno=MINOR(dev);
                pr_info("%s : MajorNo=%d  and MinorNo=%d\n",__func__,majorno,minorno);
        ret=0;
                cdev_init(&serialdev.cdev , &uart_fops);
                ret= cdev_add(&serialdev.cdev,dev,1);
                if(ret<0)
                {
                                pr_err("%s: failed in cdev_add \n",__func__);
                                goto err_cdev_del;
                }
        pr_info("%s: Hello from Raspberry_Pi\n",__func__);
                //class create                                                    
		
		pl011_uart_class=class_create(THIS_MODULE,"pl011_uart_class");
                if(IS_ERR(pl011_uart_class))
                {
                                pr_err("pl011 failed to creat class\n");
                                ret=PTR_ERR(pl011_uart_class);
                                goto err_cdev_del;
                }
                pl011_uart_device=device_create(pl011_uart_class,NULL,dev,NULL,"pl011_uart");
                if(IS_ERR(pl011_uart_device))
                {
                                pr_err("failed to creat device");
                                ret=PTR_ERR(pl011_uart_device);
                                goto err_class;
                }
                pr_info("%s:Device Created\n",__func__);
                //map uart register//                                                                                  
        uart_base_addr = ioremap(UART_BASE,UART_SIZE);
                if(!uart_base_addr)
                {
                                pr_err("failed to map uart register");
                                goto err_device;
                }
                pr_info("pl011 _uart : uartmapped at virtual address %p\n",uart_base_addr);

                //validate MMIO by reading FR register//    
	#ifndef DEBUG
      	 	fr = readl(uart_base_addr + UART_FR);
                pr_info("pl011 _uart : uart:UARTS FR Register = 0x%x\n",fr);
	#endif

	//Config Uarts GPIO pins>>>>>>
	config_gpio_uart5();

	/// init 
	uart_init();

	///.......init atomic variable.........................
	atomic_set(&serialdev.available,1);
                pr_info("pl011 _uart : uart:UARTS initialized\n");


#ifndef DEBUG
       pr_info("%s:End\n",__func__);
#endif
                return 0;

err_device:
          iounmap(uart_base_addr);
          device_destroy(pl011_uart_class,dev);

err_class:
         class_destroy(pl011_uart_class);

err_cdev_del:
            cdev_del(&serialdev.cdev);

err_unregister_chrdev:
             unregister_chrdev_region(dev ,nod);
                         return -1;

}
module_init(uart_init);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PL011 UART DRIVER FOR BCM2711");
MODULE_AUTHOR("Amaan_Waris");

