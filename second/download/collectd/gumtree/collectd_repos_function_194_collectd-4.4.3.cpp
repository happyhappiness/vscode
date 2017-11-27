static int us_init (void)
{
	int status;

	loop = 1;

	status = pthread_create (&listen_thread, NULL, us_server_thread, NULL);
	if (status != 0)
	{
		char errbuf[1024];
		ERROR ("unixsock plugin: pthread_create failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	return (0);
}