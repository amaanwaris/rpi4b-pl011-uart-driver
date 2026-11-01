#include"header.h"
#include"declaration.h"
int uart_open(struct inode *inode, struct file *file)
{
	Serialdev *serialdev;

#ifndef DEBUG
		pr_info("%s: Begin open\n",__func__);
#endif
		serialdev = container_of(inode->i_cdev,Serialdev,cdev);
		file->private_data = serialdev;

		if(atomic_dec_and_test(&serialdev->available)==0)
		{
			atomic_inc(&serialdev->available);
			pr_err("Device busy\n");
			return -EBUSY;
		}


#ifndef DEBUG
        pr_info("%s: End open\n",__func__);
#endif
		return 0;
}
