#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Margarita Sakhno");
MODULE_DESCRIPTION("Lab 5: Hello2 Module Caller");

static uint repeat_count = 1;
module_param(repeat_count, uint, 0644);
MODULE_PARM_DESC(repeat_count, "The number of times to call print_hello() from hello1 module.");

static int __init hello2_init(void)
{
    unsigned int i;
    
    pr_info("Hello2: Modulw loaded with count=%u\n", repeat_count);
    
    BUG_ON(repeat_count > 10);

    if (repeat_count == 0) {
        pr_warn("Warning: repeat_count is 0.\n");
    }

    for (i = 0; i < repeat_count; i++) {
        print_hello(i + 1, repeat_count);
    }
    
    pr_info("Hello2 module loaded. Finished calls to hello1.\n");
    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("Hello2 module unloaded.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
