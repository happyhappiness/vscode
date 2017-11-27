static int sigrok_init(void)
{
	int status;

	if (sr_thread_running) {
		ERROR("sigrok plugin: Thread already running.");
		return -1;
	}

	status = plugin_thread_create(&sr_thread, NULL, sigrok_read_thread,
			NULL);
	if (status != 0)
	{
		char errbuf[1024];
		ERROR("sigrok plugin: Failed to create thread: %s.",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return -1;
	}
	sr_thread_running = TRUE;

	return 0;
}