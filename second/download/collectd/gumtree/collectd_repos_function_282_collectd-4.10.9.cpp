static int net_shutdown (int *fd)
{
	uint16_t packet_size = 0;

	if ((fd == NULL) || (*fd < 0))
		return (EINVAL);

	swrite (*fd, (void *) &packet_size, sizeof (packet_size));
	close (*fd);
	*fd = -1;

	return (0);
}