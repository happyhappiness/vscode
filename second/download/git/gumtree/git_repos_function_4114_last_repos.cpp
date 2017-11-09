static void cleanup_dir_mutex(void)
{
	int j;

	for (j = 0; j < LAZY_MAX_MUTEX; j++)
		pthread_mutex_destroy(&lazy_dir_mutex_array[j]);

	free(lazy_dir_mutex_array);
}