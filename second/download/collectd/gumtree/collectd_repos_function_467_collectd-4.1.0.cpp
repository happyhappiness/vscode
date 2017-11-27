static int rrd_shutdown (void)
{
	pthread_mutex_lock (&cache_lock);
	rrd_cache_flush (-1);
	pthread_mutex_unlock (&cache_lock);

	pthread_mutex_lock (&queue_lock);
	do_shutdown = 1;
	pthread_cond_signal (&queue_cond);
	pthread_mutex_unlock (&queue_lock);

	return (0);
}