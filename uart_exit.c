#include"header.h"
#include"declaration.h"

static void __exit uart_exit(void)
{		
#ifndef DEBUG
	pr_info("%s:BYE Kernel\n",__func__);
#endif
void __iomem *uart_base_addr;

    
	iounmap(uart_base_addr);
	device_destroy(pl011_uart_class,dev);
	class_destroy(pl011_uart_class);
    	cdev_del(&serialdev.cdev);
	unregister_chrdev_region(dev ,nod);
	pr_info("%s:Driver removed\n",__func__);
    


#ifndef DEBUG
	pr_info("%s: End Kernel\n",__func__);
#endif
	
}
module_exit(uart_exit);
