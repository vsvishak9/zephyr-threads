#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACKSIZE 1024
#define PRIORITY  1

K_THREAD_STACK_DEFINE(thread1_stack, STACKSIZE);
K_THREAD_STACK_DEFINE(thread2_stack, STACKSIZE);

K_QUEUE_DEFINE(msq_queue);

typedef struct data_share {
	char *message;
	int delay; // in ms
} data_share;

void thread1fn(void *a1, void *a2, void *a3)
{
	static data_share d1 = {"Hi there this data shared through queues", 500}; // delay in ms
	int delay = 1;
	while (1) {
		printk("thread 1\n");
		k_queue_alloc_append(&msq_queue, &d1);
		k_sleep(K_SECONDS(delay));
		delay += 1;
		if (delay > 10)
			delay = 1;
	}
}

void thread2fn(void *a1, void *a2, void *a3)
{
	while (1) {
		data_share *data = k_queue_get(&msq_queue, K_FOREVER);
		int delay = data->delay;
		k_sleep(K_MSEC(delay));
		printk("thread 2 recieved message: %s\n", data->message);
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
