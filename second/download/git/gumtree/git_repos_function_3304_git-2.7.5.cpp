static inline void grep_read_lock(void)
{
	if (grep_use_locks)
		pthread_mutex_lock(&grep_read_mutex);
}