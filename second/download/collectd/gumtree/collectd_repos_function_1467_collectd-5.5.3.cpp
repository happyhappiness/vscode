static void riemann_free(void *p) /* {{{ */
{
	struct riemann_host	*host = p;

	if (host == NULL)
		return;

	pthread_mutex_lock (&host->lock);

	host->reference_count--;
	if (host->reference_count > 0)
	{
		pthread_mutex_unlock (&host->lock);
		return;
	}

	riemann_disconnect (host);

	sfree(host->service);
	pthread_mutex_destroy (&host->lock);
	sfree(host);
}