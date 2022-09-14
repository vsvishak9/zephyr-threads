#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACKSIZE 1024
#define PRIORITY  7

K_THREAD_STACK_DEFINE(thread1_stack, STACKSIZE);

void printfn()
{
	int delay = 1000;
	while (1) {
		printk("thread 1\n");
		k_sleep(K_MSEC(delay));
		delay += 1000;
		if (delay > 10000)
			delay = 1000;
	}
}

void thread1fn(void *a1, void *a2, void *a3)
{
	printfn();
}

void main(void)
{
	static struct k_thread thread1_data;
	k_tid_t thread1_id =
		k_thread_create(&thread1_data, thread1_stack, K_THREAD_STACK_SIZEOF(thread1_stack),
				thread1fn, NULL, NULL, NULL, PRIORITY, 0, K_NO_WAIT);
}
