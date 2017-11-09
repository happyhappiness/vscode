static inline void lock_mutex(pthread_mutex_t *mutex)
{
	if (threads_active)
		pthread_mutex_lock(mutex);
}