static int email_init (void)
{
	int err = 0;

	if (0 != (err = plugin_thread_create (&connector, NULL,
				open_connection, NULL))) {
		char errbuf[1024];
		disabled = 1;
		log_err ("pthread_create() failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	return (0);
}