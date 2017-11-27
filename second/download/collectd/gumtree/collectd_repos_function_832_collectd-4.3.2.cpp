static void ping_free (pinghost_t *ph)
{
	if (ph->hostname != NULL)
		free (ph->hostname);

	if (ph->data != NULL)
		free (ph->data);

	free (ph);
}