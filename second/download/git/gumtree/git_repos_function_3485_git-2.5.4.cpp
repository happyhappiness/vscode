static inline void grep_attr_unlock(void)
{
	if (grep_use_locks)
		pthread_mutex_unlock(&grep_attr_mutex);
}