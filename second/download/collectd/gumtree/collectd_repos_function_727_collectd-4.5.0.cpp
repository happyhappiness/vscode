static int init_hostname (void)
{
	const char *str;

	struct addrinfo  ai_hints;
	struct addrinfo *ai_list;
	struct addrinfo *ai_ptr;
	int status;

	str = global_option_get ("Hostname");
	if (str != NULL)
	{
		sstrncpy (hostname_g, str, sizeof (hostname_g));
		return (0);
	}

	if (gethostname (hostname_g, sizeof (hostname_g)) != 0)
	{
		fprintf (stderr, "`gethostname' failed and no "
				"hostname was configured.\n");
		return (-1);
	}

	str = global_option_get ("FQDNLookup");
	if ((strcasecmp ("false", str) == 0)
			|| (strcasecmp ("no", str) == 0)
			|| (strcasecmp ("off", str) == 0))
		return (0);

	memset (&ai_hints, '\0', sizeof (ai_hints));
	ai_hints.ai_flags = AI_CANONNAME;

	status = getaddrinfo (hostname_g, NULL, &ai_hints, &ai_list);
	if (status != 0)
	{
		ERROR ("Looking up \"%s\" failed. You have set the "
				"\"FQDNLookup\" option, but I cannot resolve "
				"my hostname to a fully qualified domain "
				"name. Please fix you network "
				"configuration.", hostname_g);
		return (-1);
	}

	for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
	{
		if (ai_ptr->ai_canonname == NULL)
			continue;

		sstrncpy (hostname_g, ai_ptr->ai_canonname, sizeof (hostname_g));
		break;
	}

	freeaddrinfo (ai_list);
	return (0);
}