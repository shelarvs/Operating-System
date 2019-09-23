/*Name:- MISS SANA N PABANI
Year:- TE IT (B)
Batch:- B
Roll No:-37038


#include <linux/kernel.h>
asmlinkage long sys_hello(void)
{
	printk(KERN_INFO "Hello world\n");
	return 0;
}
