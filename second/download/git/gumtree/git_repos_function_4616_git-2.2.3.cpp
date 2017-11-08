static void set_thread_data(struct thread_local *data)
{
	if (threads_active)
		pthread_setspecific(key, data);
}