static int apcups_shutdown (void)
{
	uint16_t packet_size = 0;

	if (global_sockfd < 0)
		return (0);

	DEBUG ("Gracefully shutting down socket %i.", global_sockfd);

	/* send EOF sentinel */
	swrite (global_sockfd, (void *) &packet_size, sizeof (packet_size));

	close (global_sockfd);
	global_sockfd = -1;

	return (0);
}