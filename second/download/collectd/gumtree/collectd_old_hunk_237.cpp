	struct addrinfo *ai_ptr;
	int status;

	str = global_option_get ("Hostname");
	if (str != NULL)
	{
		strncpy (hostname_g, str, sizeof (hostname_g));
		hostname_g[sizeof (hostname_g) - 1] = '\0';
		return (0);
	}

	if (gethostname (hostname_g, sizeof (hostname_g)) != 0)
	{
		fprintf (stderr, "`gethostname' failed and no "
