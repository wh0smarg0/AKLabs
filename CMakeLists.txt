// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
static uint hello_count = 1;
module_param(hello_count, uint, 0444);
MODULE_PARM_DESC(hello_count, "Number of times to print 'Hello, world!'");
static LIST_HEAD(hello_list);
struct hello_event {
struct list_head list;
ktime_t timestamp;
};
static int __init hello_init(void)
{
int i;
struct hello_event *event;
if (hello_count == 0 || (hello_count >= 5 && hello_count <= 10)) {
pr_warn("Warning: hello_count is %u\n", hello_count);
} else if (hello_count > 10) {
pr_err("Error: hello_count is too large, must be <= 10\n");
return -EINVAL;
}
for (i = 0; i < hello_count; i++) {
pr_info("Hello, world!\n");
event = kmalloc(sizeof(*event), GFP_KERNEL);
if (!event) {
pr_err("Failed to allocate memory\n");
return -ENOMEM;
}
event->timestamp = ktime_get();
list_add_tail(&event->list, &hello_list);
}
return 0;
}
static void __exit hello_exit(void)
{
struct hello_event *event;
list_for_each_entry(event, &hello_list, list) {
pr_info("Event time: %lld ns\n", ktime_to_ns(event->timestamp));
kfree(event);
}
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Margaryta");
MODULE_DESCRIPTION("A simple Hello World kernel module with parameters");
