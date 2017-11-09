static inline void grep_unlock(void)
{
	assert(num_threads);
	pthread_mutex_unlock(&grep_mutex);
}