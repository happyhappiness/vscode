static inline void vector_lock(void)
{
#ifndef NO_PTHREADS
	pthread_mutex_lock(&check_vector.mutex);
#endif
}