		printf ("UNKNOWN: %s\n", lcc_strerror (connection));
		if (ret_ident != NULL)
			free (ret_ident);
		return (RET_UNKNOWN);
	}

	for (i = 0; i < ret_ident_num; ++i) {
		char id[1024];

		if ((hostname_g != NULL) && (strcasecmp (hostname_g, ret_ident[i].host)))
			continue;

		if ((hostname == NULL) || strcasecmp (hostname, ret_ident[i].host))
