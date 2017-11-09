static inline void grep_lock(void)
{
	assert(num_threads);
	pthread_mutex_lock(&grep_mutex);
}