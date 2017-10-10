
	if (!(config_file = fopen(config_filename, "rb"))) {
		/* no config file means nothing to rename, no error */
		goto unlock_and_out;
	}

	while (fgets(buf, sizeof(buf), config_file)) {
		int i;
		int length;
		char *output = buf;
		for (i = 0; buf[i] && isspace(buf[i]); i++)
			; /* do nothing */
