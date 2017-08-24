{
	unsigned i;

	for (i = 0; i < 512; i++)
		if (*p++)
			return (0);
	return (1);
}