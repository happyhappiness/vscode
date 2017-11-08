static inline void grep_unlock(void)
{
	if (use_threads)
		pthread_mutex_unlock(&grep_mutex);
}