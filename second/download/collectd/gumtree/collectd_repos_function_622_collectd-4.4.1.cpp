static int rrd_flush (const int timeout)
{
	pthread_mutex_lock (&cache_lock);

	if (cache == NULL) {
		pthread_mutex_unlock (&cache_lock);
		return (0);
	}

	rrd_cache_flush (timeout);
	pthread_mutex_unlock (&cache_lock);
	return (0);
}