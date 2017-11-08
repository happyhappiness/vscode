static void cleanup_thread(void)
{
	int i;
	if (!threads_active)
		return;
	threads_active = 0;
	pthread_mutex_destroy(&read_mutex);
	pthread_mutex_destroy(&counter_mutex);
	pthread_mutex_destroy(&work_mutex);
	pthread_mutex_destroy(&type_cas_mutex);
	if (show_stat)
		pthread_mutex_destroy(&deepest_delta_mutex);
	for (i = 0; i < nr_threads; i++)
		close(thread_data[i].pack_fd);
	pthread_key_delete(key);
	free(thread_data);
}