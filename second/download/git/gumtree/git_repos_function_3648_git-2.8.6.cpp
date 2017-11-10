static inline void grep_attr_lock(void)
{
	if (grep_use_locks)
		pthread_mutex_lock(&grep_attr_mutex);
}