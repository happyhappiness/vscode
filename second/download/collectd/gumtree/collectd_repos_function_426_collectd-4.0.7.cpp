static int rrd_init (void)
{
	if (stepsize <= 0)
		stepsize = interval_g;
	if (heartbeat <= 0)
		heartbeat = 2 * interval_g;

	if (heartbeat < interval_g)
		WARNING ("rrdtool plugin: Your `heartbeat' is "
				"smaller than your `interval'. This will "
				"likely cause problems.");
	else if (stepsize < interval_g)
		WARNING ("rrdtool plugin: Your `stepsize' is "
				"smaller than your `interval'. This will "
				"create needlessly big RRD-files.");

	pthread_mutex_lock (&cache_lock);
	if (cache_timeout < 2)
	{
		cache_timeout = 0;
		cache_flush_timeout = 0;
	}
	else
	{
		if (cache_flush_timeout < cache_timeout)
			cache_flush_timeout = 10 * cache_timeout;

		cache = avl_create ((int (*) (const void *, const void *)) strcmp);
		cache_flush_last = time (NULL);
		plugin_register_shutdown ("rrdtool", rrd_shutdown);
	}
	pthread_mutex_unlock (&cache_lock);

	DEBUG ("rrdtool plugin: rrd_init: datadir = %s; stepsize = %i;"
			" heartbeat = %i; rrarows = %i; xff = %lf;",
			(datadir == NULL) ? "(null)" : datadir,
			stepsize, heartbeat, rrarows, xff);

	return (0);
}