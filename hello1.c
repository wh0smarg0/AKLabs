#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Margarita Sakhno");
MODULE_DESCRIPTION("Lab 5: Hello1 Module with List and Timing");

struct event_data {
  struct list_head list;
  ktime_t duration;
};

static LIST_HEAD(event_list);

void print_hello(unsigned int current_count, unsigned int total_count)
{
    struct event_data *data;
    ktime_t start, end;
    
    start = ktime_get();
    
    pr_info("Hello, world! (%u/%u)\n", current_count, total_count);
    
    end = ktime_get();
    
    data = kmalloc(sizeof(*data), GFP_KERNEL);
    if (!data) {
        pr_err("Hello1: Memory allocation failed\n");
        return;
    }

    data->duration = ktime_sub(end, start);
    list_add_tail(&data->list, &event_list);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
    pr_info("Hello1: Module loaded. Providing print_hello symbol.\n");
    return 0;
}

static void __exit hello1_exit(void)
{
    struct event_data *data, *tmp;

    pr_info("Hello1: Module cleanup: printing time diffs.\n");

    list_for_each_entry_safe(data, tmp, &event_list, list) {
        
        pr_info("Event time diff (ns): %lld\n", ktime_to_ns(data->duration));
        list_del(&data->list);
        kfree(data);
    }
    pr_info("Hello1 module finished.\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
