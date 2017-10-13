static void init_thread(void)
{
	int i;
	init_recursive_mutex(&read_mutex);
	pthread_mutex_init(&counter_mutex, NULL);
	pthread_mutex_init(&work_mutex, NULL);
	if (show_stat)
		pthread_mutex_init(&deepest_delta_mutex, NULL);
	pthread_key_create(&key, NULL);
	thread_data = xcalloc(nr_threads, sizeof(*thread_data));
	for (i = 0; i < nr_threads; i++) {
		thread_data[i].pack_fd = open(curr_pack, O_RDONLY);
		if (thread_data[i].pack_fd == -1)
			die_errno(_("unable to open %s"), curr_pack);
	}

	threads_active = 1;
}