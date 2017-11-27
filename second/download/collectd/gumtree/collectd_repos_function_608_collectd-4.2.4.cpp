static int network_init (void)
{
	plugin_register_shutdown ("network", network_shutdown);

	send_buffer_ptr  = send_buffer;
	send_buffer_fill = 0;
	memset (&send_buffer_vl, '\0', sizeof (send_buffer_vl));
	memset (send_buffer_type, '\0', sizeof (send_buffer_type));

	cache_tree = c_avl_create ((int (*) (const void *, const void *)) strcmp);
	cache_flush_last = time (NULL);

	/* setup socket(s) and so on */
	if (sending_sockets != NULL)
		plugin_register_write ("network", network_write);

	if ((listen_sockets_num != 0) && (listen_thread == 0))
	{
		int status;

		status = pthread_create (&listen_thread, NULL /* no attributes */,
				receive_thread, NULL /* no argument */);

		if (status != 0)
		{
			char errbuf[1024];
			ERROR ("network: pthread_create failed: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
		}
	}
	return (0);
}