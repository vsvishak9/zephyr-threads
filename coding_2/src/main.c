#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACKSIZE 1024
#define PRIORITY  7

K_THREAD_STACK_DEFINE(thread1_stack, STACKSIZE);
K_THREAD_STACK_DEFINE(thread2_stack, STACKSIZE);

K_QUEUE_DEFINE(msq_queue);
int delay = 1;
void thread1fn(void *a1, void *a2, void *a3)
{

	while (1) {
		printk("thread 1\n");
		k_queue_alloc_append(&msq_queue, &delay);
		k_sleep(K_SECONDS(delay));
		delay += 1;
		if (delay > 10)
			delay = 1;
	}
}

void thread2fn(void *a1, void *a2, void *a3)
{
	while (1) {
		int *data = k_queue_get(&msq_queue, K_FOREVER);
		int data_int = *data;
		k_sleep(K_SECONDS(1));
		printk("thread 2\n");
	}
}

void main(void)
{
	static struct k_thread thread1_data;
	static struct k_thread thread2_data;
	k_tid_t thread2_id =
		k_thread_create(&thread2_data, thread2_stack, K_THREAD_STACK_SIZEOF(thread2_stack),
				thread2fn, NULL, NULL, NULL, PRIORITY, 0, K_NO_WAIT);
	k_tid_t thread1_id =
		k_thread_create(&thread1_data, thread1_stack, K_THREAD_STACK_SIZEOF(thread1_stack),
				thread1fn, NULL, NULL, NULL, PRIORITY, 0, K_NO_WAIT);
}
