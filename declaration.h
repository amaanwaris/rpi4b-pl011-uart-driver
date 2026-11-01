extern dev_t dev;
extern int majorno,minorno,nod;
//extern void __iomen *uart_base_addr;
typedef struct
{
		atomic_t available;
		struct cdev cdev;
}Serialdev;

extern Serialdev serialdev;
extern struct class *pl011_uart_class;
extern struct device *pl011_uart_device;

int uart_open(struct inode *inode , struct file *file);
int uart_close(struct inode *inode , struct file *file);
size_t uart_write(struct file *file ,const char __user *buff , size_t len , loff_t *offset);
//ssize_t uart_read(struct file *file , char __user *buff , size_t len ,loff_t *offset);
