
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define MSG	"Hello World!\n"
#define MSGLEN	strlen(MSG)


static ssize_t sample_read_proc(struct file *filp, char __user *buffer, size_t length, loff_t *offset){
    //	/proc/sample always outputs MSG
    static int run = 0;
    run = !run;
    if(run){
        copy_to_user(buffer, MSG, MSGLEN);
        return MSGLEN;
    }
    return 0;
}


static const struct file_operations fops = {
    .owner = THIS_MODULE,
    .open  = NULL,
    .read  = sample_read_proc,
    .write = NULL,
};


struct proc_dir_entry *pde;


static int __init init_test(void){
    pde = proc_create("sample", 0, NULL, &fops);
    printk(KERN_INFO "Init sample!\n");
    return 0;
}


static void __exit exit_test(void){
    proc_remove(pde);
    printk(KERN_INFO "Exit sample!\n");
}


module_init(init_test);
module_exit(exit_test);
MODULE_LICENSE("GPL");

