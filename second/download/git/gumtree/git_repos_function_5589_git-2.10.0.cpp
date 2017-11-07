static inline void grep_lock(void)
{
	if (num_threads)
		pthread_mutex_lock(&grep_mutex);
}