static void init_dir_mutex(void)
{
	int j;

	lazy_dir_mutex_array = xcalloc(LAZY_MAX_MUTEX, sizeof(pthread_mutex_t));

	for (j = 0; j < LAZY_MAX_MUTEX; j++)
		init_recursive_mutex(&lazy_dir_mutex_array[j]);
}