{
	int			i;

	if (e == 0)
	{
		errno = 0;
		return;
	}

	for (i = 0; i < (int)(sizeof(doserrors)/sizeof(doserrors[0])); i++)
	{
		if (doserrors[i].winerr == e)
		{
			errno = doserrors[i].doserr;
			return;
		}
	}

	/* fprintf(stderr, "unrecognized win32 error code: %lu", e); */
	errno = EINVAL;
	return;
}