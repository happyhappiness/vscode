static inline void grep_read_unlock(void)
{
	if (grep_use_locks)
		pthread_mutex_unlock(&grep_read_mutex);
}