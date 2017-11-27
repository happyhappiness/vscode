static int multimeter_shutdown (void)
{
	if (fd >= 0)
	{
		close (fd);
		fd = -1;
	}

	return (0);
}