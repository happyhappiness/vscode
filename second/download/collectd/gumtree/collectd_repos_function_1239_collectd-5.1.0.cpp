static int rrd_shutdown (void)
{
	pthread_mutex_lock (&cache_lock);
	rrd_cache_flush (0);
	pthread_mutex_unlock (&cache_lock);

	pthread_mutex_lock (&queue_lock);
	do_shutdown = 1;
	pthread_cond_signal (&queue_cond);
	pthread_mutex_unlock (&queue_lock);

	if ((queue_thread_running != 0)
			&& ((queue_head != NULL) || (flushq_head != NULL)))
	{
		INFO ("rrdtool plugin: Shutting down the queue thread. "
				"This may take a while.");
	}
	else if (queue_thread_running != 0)
	{
		INFO ("rrdtool plugin: Shutting down the queue thread.");
	}

	/* Wait for all the values to be written to disk before returning. */
	if (queue_thread_running != 0)
	{
		pthread_join (queue_thread, NULL);
		memset (&queue_thread, 0, sizeof (queue_thread));
		queue_thread_running = 0;
		DEBUG ("rrdtool plugin: queue_thread exited.");
	}

	rrd_cache_destroy ();

	return (0);
}