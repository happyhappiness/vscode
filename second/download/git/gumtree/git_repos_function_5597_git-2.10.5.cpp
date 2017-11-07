static inline void grep_unlock(void)
{
	if (num_threads)
		pthread_mutex_unlock(&grep_mutex);
}