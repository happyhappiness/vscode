static int rrd_init (void)
{
	int status;

	if (stepsize < 0)
		stepsize = 0;
	if (heartbeat <= 0)
	{
		if (stepsize > 0)
			heartbeat = 2 * stepsize;
		else
			heartbeat = 0;
	}

	if ((heartbeat > 0) && (heartbeat < interval_g))
		WARNING ("rrdtool plugin: Your `heartbeat' is "
				"smaller than your `interval'. This will "
				"likely cause problems.");
	else if ((stepsize > 0) && (stepsize < interval_g))
		WARNING ("rrdtool plugin: Your `stepsize' is "
				"smaller than your `interval'. This will "
				"create needlessly big RRD-files.");

	/* Set the cache up */
	pthread_mutex_lock (&cache_lock);

	cache = c_avl_create ((int (*) (const void *, const void *)) strcmp);
	if (cache == NULL)
	{
		ERROR ("rrdtool plugin: c_avl_create failed.");
		return (-1);
	}

	cache_flush_last = time (NULL);
	if (cache_timeout < 2)
	{
		cache_timeout = 0;
		cache_flush_timeout = 0;
	}
	else if (cache_flush_timeout < cache_timeout)
		cache_flush_timeout = 10 * cache_timeout;

	pthread_mutex_unlock (&cache_lock);

	status = pthread_create (&queue_thread, NULL, rrd_queue_thread, NULL);
	if (status != 0)
	{
		ERROR ("rrdtool plugin: Cannot create queue-thread.");
		return (-1);
	}

	DEBUG ("rrdtool plugin: rrd_init: datadir = %s; stepsize = %i;"
			" heartbeat = %i; rrarows = %i; xff = %lf;",
			(datadir == NULL) ? "(null)" : datadir,
			stepsize, heartbeat, rrarows, xff);

	return (0);
}