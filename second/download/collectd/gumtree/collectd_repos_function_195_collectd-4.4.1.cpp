static int us_shutdown (void)
{
	void *ret;

	loop = 0;

	if (listen_thread != (pthread_t) 0)
	{
		pthread_kill (listen_thread, SIGTERM);
		pthread_join (listen_thread, &ret);
		listen_thread = (pthread_t) 0;
	}

	plugin_unregister_init ("unixsock");
	plugin_unregister_shutdown ("unixsock");

	return (0);
}