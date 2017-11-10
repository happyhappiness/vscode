static inline struct thread_local *get_thread_data(void)
{
#ifndef NO_PTHREADS
	if (threads_active)
		return pthread_getspecific(key);
	assert(!threads_active &&
	       "This should only be reached when all threads are gone");
#endif
	return &nothread_data;
}