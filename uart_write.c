#include "header.h"
#include "declaration.h"

static void uart_send_char(char ch)
{
#ifdef DEBUG
	pr_info("uart_send_char\n");
#endif
	u32 fr;

    	/* Wait until TX FIFO not full */
    	do
    	{
        	fr = readl(uart_base_addr + UART_FR);
    	} 

	while (fr & (1 << 5));

    		if (ch == '\n')
        		uart_send_char('\r');

    	/* Write character into UART Data Register */
    	writel(ch, uart_base_addr + UART_DR);

    	pr_info("pl011_uart:UART5 TX -> %c\n", ch);
}

static void uart_send_string(const char *str)
{
    	while (*str)
    	{
        	uart_send_char(*str);
        	str++;
    	}
}

ssize_t uart_write(struct file *file,const char __user *buf,size_t len,loff_t *offset)
{
	char ch;
    	char kbuf[128];
    	unsigned long ret;

    	pr_info("write function called\n");

    	// check len first and prevent buffer overflow ****************
    	if (len > sizeof(kbuf) - 1)
    	{
        	len = sizeof(kbuf) - 1;
    	}

    	// copy data from user space to kernel buffer ****************
    	ret = copy_from_user(kbuf, buf, len);

    	if (ret > 0)
    	{
     		return -EFAULT;
    	}

    	kbuff[len] = '\0';  // add NULL st the end of string
    	uart_send_string(kbuf); // send to send string function...

#ifdef DEBUG
	pr_info("UART TX: %s\n",kbuf);
#endif

#ifdef DEBUG
	pr_info("End Write Function\n");
#endif

	return len;
}
