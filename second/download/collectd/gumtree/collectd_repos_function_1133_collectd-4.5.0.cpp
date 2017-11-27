static int ping_get_ident (void)
{
	int fd;
	static int did_seed = 0;

	int retval;

	if (did_seed == 0)
	{
		if ((fd = open ("/dev/urandom", O_RDONLY)) != -1)
		{
			unsigned int seed;

			if (read (fd, &seed, sizeof (seed)) != -1)
			{
				did_seed = 1;
				dprintf ("Random seed: %i\n", seed);
				srandom (seed);
			}

			close (fd);
		}
		else
		{
			dprintf ("open (/dev/urandom): %s\n", strerror (errno));
		}
	}

	retval = (int) random ();

	dprintf ("Random number: %i\n", retval);
	
	return (retval);
}