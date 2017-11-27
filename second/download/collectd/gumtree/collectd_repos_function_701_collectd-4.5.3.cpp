static int rrd_flush (int timeout, const char *identifier)
{
	pthread_mutex_lock (&cache_lock);

	if (cache == NULL) {
		pthread_mutex_unlock (&cache_lock);
		return (0);
	}

	rrd_cache_flush_identifier (timeout, identifier);

	pthread_mutex_unlock (&cache_lock);
	return (0);
}