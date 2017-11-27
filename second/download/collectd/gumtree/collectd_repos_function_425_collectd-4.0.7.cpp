static int rrd_shutdown (void)
{
	pthread_mutex_lock (&cache_lock);
	rrd_cache_flush (-1);
	if (cache != NULL)
		avl_destroy (cache);
	cache = NULL;
	pthread_mutex_unlock (&cache_lock);

	return (0);
}