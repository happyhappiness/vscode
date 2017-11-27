static int riemann_send(struct riemann_host *host, Msg const *msg) /* {{{ */
{
	int status = 0;
	pthread_mutex_lock (&host->lock);

	status = riemann_send_msg(host, msg);
	if (status != 0) {
		riemann_disconnect (host);
		pthread_mutex_unlock (&host->lock);
		return status;
	}

	/*
	 * For TCP we need to receive message acknowledgemenent.
	 */
	if (host->use_tcp)
	{
		status = riemann_recv_ack(host);

		if (status != 0)
		{
			riemann_disconnect (host);
			pthread_mutex_unlock (&host->lock);
			return status;
		}
	}

	pthread_mutex_unlock (&host->lock);
	return 0;
}