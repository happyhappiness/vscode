static inline void grep_lock(void)
{
	if (use_threads)
		pthread_mutex_lock(&grep_mutex);
}