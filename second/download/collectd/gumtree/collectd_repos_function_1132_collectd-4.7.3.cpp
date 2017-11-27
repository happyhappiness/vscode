static int network_init (void)
{
	/* Check if we were already initialized. If so, just return - there's
	 * nothing more to do (for now, that is). */
	if (cache_flush_last != 0)
		return (0);

#if HAVE_LIBGCRYPT
	gcry_control (GCRYCTL_SET_THREAD_CBS, &gcry_threads_pthread);
	gcry_control (GCRYCTL_INIT_SECMEM, 32768, 0);
	gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);
#endif

	plugin_register_shutdown ("network", network_shutdown);

	network_init_buffer ();

	cache_tree = c_avl_create ((int (*) (const void *, const void *)) strcmp);
	cache_flush_last = time (NULL);

	/* setup socket(s) and so on */
	if (sending_sockets != NULL)
	{
		plugin_register_write ("network", network_write,
				/* user_data = */ NULL);
		plugin_register_notification ("network", network_notification,
				/* user_data = */ NULL);
	}

	/* If no threads need to be started, return here. */
	if ((listen_sockets_num == 0)
			|| ((dispatch_thread_running != 0)
				&& (receive_thread_running != 0)))
		return (0);

	if (dispatch_thread_running == 0)
	{
		int status;
		status = pthread_create (&dispatch_thread_id,
				NULL /* no attributes */,
				dispatch_thread,
				NULL /* no argument */);
		if (status != 0)
		{
			char errbuf[1024];
			ERROR ("network: pthread_create failed: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
		}
		else
		{
			dispatch_thread_running = 1;
		}
	}

	if (receive_thread_running == 0)
	{
		int status;
		status = pthread_create (&receive_thread_id,
				NULL /* no attributes */,
				receive_thread,
				NULL /* no argument */);
		if (status != 0)
		{
			char errbuf[1024];
			ERROR ("network: pthread_create failed: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
		}
		else
		{
			receive_thread_running = 1;
		}
	}

	return (0);
}