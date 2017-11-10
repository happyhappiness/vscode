static inline void unlock_mutex(pthread_mutex_t *mutex)
{
	if (threads_active)
		pthread_mutex_unlock(mutex);
}