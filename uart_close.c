#include"header.h"
#include"declaration.h"

int uart_close(struct inode * inode, struct file * file)
{
#ifndef DEBUG
		pr_info("%s: Begin close\n",__func__);
#endif
		Serialdev *serialdev;

		serialdev = file->private_data;
		atomic_inc(&serialdev->available);

#ifndef DEBUG
        pr_info("%s: End close\n",__func__);
#endif
		return 0;
}
