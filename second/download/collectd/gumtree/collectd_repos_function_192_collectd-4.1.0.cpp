static void *us_server_thread (void *arg)
{
	int  status;
	int *remote_fd;
	pthread_t th;
	pthread_attr_t th_attr;

	if (us_open_socket () != 0)
		pthread_exit ((void *) 1);

	while (loop != 0)
	{
		DEBUG ("Calling accept..");
		status = accept (sock_fd, NULL, NULL);
		if (status < 0)
		{
			char errbuf[1024];

			if (errno == EINTR)
				continue;

			ERROR ("unixsock plugin: accept failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			close (sock_fd);
			sock_fd = -1;
			pthread_exit ((void *) 1);
		}

		remote_fd = (int *) malloc (sizeof (int));
		if (remote_fd == NULL)
		{
			char errbuf[1024];
			WARNING ("unixsock plugin: malloc failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			close (status);
			continue;
		}
		*remote_fd = status;

		DEBUG ("Spawning child to handle connection on fd #%i", *remote_fd);

		pthread_attr_init (&th_attr);
		pthread_attr_setdetachstate (&th_attr, PTHREAD_CREATE_DETACHED);

		status = pthread_create (&th, &th_attr, us_handle_client, (void *) remote_fd);
		if (status != 0)
		{
			char errbuf[1024];
			WARNING ("unixsock plugin: pthread_create failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			close (*remote_fd);
			free (remote_fd);
			continue;
		}
	} /* while (loop) */

	close (sock_fd);
	sock_fd = -1;

	status = unlink ((sock_file != NULL) ? sock_file : US_DEFAULT_PATH);
	if (status != 0)
	{
		char errbuf[1024];
		NOTICE ("unixsock plugin: unlink (%s) failed: %s",
				(sock_file != NULL) ? sock_file : US_DEFAULT_PATH,
				sstrerror (errno, errbuf, sizeof (errbuf)));
	}

	return ((void *) 0);
}