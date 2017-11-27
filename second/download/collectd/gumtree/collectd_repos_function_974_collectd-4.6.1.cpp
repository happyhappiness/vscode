static int network_write (const data_set_t *ds, const value_list_t *vl)
{
	int status;

	/* If the value is already in the cache, we have received it via the
	 * network. We write it again if forwarding is activated. It's then in
	 * the cache and should we receive it again we will ignore it. */
	status = cache_check (vl);
	if ((network_config_forward == 0)
			&& (status != 0))
		return (0);

	pthread_mutex_lock (&send_buffer_lock);

	status = add_to_buffer (send_buffer_ptr,
			sizeof (send_buffer) - send_buffer_fill,
			&send_buffer_vl,
			ds, vl);
	if (status >= 0)
	{
		/* status == bytes added to the buffer */
		send_buffer_fill += status;
		send_buffer_ptr  += status;
	}
	else
	{
		flush_buffer ();

		status = add_to_buffer (send_buffer_ptr,
				sizeof (send_buffer) - send_buffer_fill,
				&send_buffer_vl,
				ds, vl);

		if (status >= 0)
		{
			send_buffer_fill += status;
			send_buffer_ptr  += status;
		}
	}

	if (status < 0)
	{
		ERROR ("network plugin: Unable to append to the "
				"buffer for some weird reason");
	}
	else if ((sizeof (send_buffer) - send_buffer_fill) < 15)
	{
		flush_buffer ();
	}

	pthread_mutex_unlock (&send_buffer_lock);

	return ((status < 0) ? -1 : 0);
}