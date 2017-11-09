static void unlock_dir_mutex(int j)
{
	pthread_mutex_unlock(&lazy_dir_mutex_array[j]);
}