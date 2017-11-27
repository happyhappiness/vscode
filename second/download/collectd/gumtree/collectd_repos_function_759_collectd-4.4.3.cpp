static int network_flush (int timeout)
{
	pthread_mutex_lock (&send_buffer_lock);

	if (((time (NULL) - cache_flush_last) >= timeout)
			&& (send_buffer_fill > 0))
	{
		flush_buffer ();
	}

	pthread_mutex_unlock (&send_buffer_lock);

	return (0);
}