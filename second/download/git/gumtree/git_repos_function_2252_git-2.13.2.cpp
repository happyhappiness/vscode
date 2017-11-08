void attr_start(void)
{
#ifndef NO_PTHREADS
	pthread_mutex_init(&g_attr_hashmap.mutex, NULL);
	pthread_mutex_init(&check_vector.mutex, NULL);
#endif
}