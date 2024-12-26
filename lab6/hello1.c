#include <hello1.h>

MODULE_AUTHOR("Andrii Bodnar");
MODULE_DESCRIPTION("Lab5 Module hello2.c");
MODULE_LICENSE("Dual BSD/GPL");

struct myStruct {
    struct list_head list;
    ktime_t startTime;
    ktime_t finishTime;
};

// статична зміна голови списку
static LIST_HEAD(myList);
int counter;

int print_hello(uint param)
{
    BUG_ON(param > 10);

    if (param == 0 || (param <= 10 && param >= 5)) {
          pr_emerg("Warning: %u\n", param);
    }

    counter = 0;
    while (counter != param) {
   // Оголошення вказівника на область пам'яті, виділену під структуру, виділення блоку
 // пам'яті заданого розміру
          struct myStruct *ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
	  ptr=0;
          ptr->startTime = ktime_get();
          pr_emerg("Hello world!\n");
          ptr->finishTime = ktime_get();
          list_add_tail(&ptr->list, &myList); // вставлення нового елементу в кінець списку
          counter += 1;
    }
    return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
    return 0;
}

static void __exit hello1_exit(void)
{
    struct myStruct *ptr, *next;

    list_for_each_entry_safe(ptr, next, &myList, list) {
          pr_emerg("Time in nanoseconds: %lld\n", ptr->finishTime - ptr->startTime);
          list_del(&ptr->list);
          kfree(ptr);
    }
}

module_init(hello1_init);
module_exit(hello1_exit);
