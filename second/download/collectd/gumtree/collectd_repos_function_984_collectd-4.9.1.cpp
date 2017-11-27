static int dns_init (void)
{
	/* clean up an old thread */
	int status;

	pthread_mutex_lock (&traffic_mutex);
	tr_queries   = 0;
	tr_responses = 0;
	pthread_mutex_unlock (&traffic_mutex);

	if (listen_thread_init != 0)
		return (-1);

	status = pthread_create (&listen_thread, NULL, dns_child_loop,
			(void *) 0);
	if (status != 0)
	{
		char errbuf[1024];
		ERROR ("dns plugin: pthread_create failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	listen_thread_init = 1;

	return (0);
}