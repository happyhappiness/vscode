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
