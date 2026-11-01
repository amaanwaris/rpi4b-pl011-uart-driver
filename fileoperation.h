struct file_operations uart_fops=
{
	owner:THIS_MODULE,
        open:uart_open,
        release:uart_close,
       // read:uart_read,
       // write:uart_write,
        //llseek:lseekMyCDD
};

