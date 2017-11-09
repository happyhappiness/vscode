static inline void vector_unlock(void)
{
#ifndef NO_PTHREADS
	pthread_mutex_unlock(&check_vector.mutex);
#endif
}