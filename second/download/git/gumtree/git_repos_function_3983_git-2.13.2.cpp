static void lock_dir_mutex(int j)
{
	pthread_mutex_lock(&lazy_dir_mutex_array[j]);
}