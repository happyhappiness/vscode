void set_socket_options(int fd, char *options)
{
	char *tok;

	if (!options || !*options)
		return;

	options = strdup(options);

	if (!options)
		out_of_memory("set_socket_options");

	for (tok = strtok(options, " \t,"); tok; tok = strtok(NULL," \t,")) {
		int ret=0,i;
		int value = 1;
		char *p;
		int got_value = 0;

		if ((p = strchr(tok,'='))) {
			*p = 0;
			value = atoi(p+1);
			got_value = 1;
		}

		for (i = 0; socket_options[i].name; i++) {
			if (strcmp(socket_options[i].name,tok)==0)
				break;
		}

		if (!socket_options[i].name) {
			rprintf(FERROR,"Unknown socket option %s\n",tok);
			continue;
		}

		switch (socket_options[i].opttype) {
		case OPT_BOOL:
		case OPT_INT:
			ret = setsockopt(fd,socket_options[i].level,
					 socket_options[i].option,
					 (char *)&value, sizeof (int));
			break;

		case OPT_ON:
			if (got_value)
				rprintf(FERROR,"syntax error -- %s does not take a value\n",tok);

			{
				int on = socket_options[i].value;
				ret = setsockopt(fd,socket_options[i].level,
						 socket_options[i].option,
						 (char *)&on, sizeof (int));
			}
			break;
		}

		if (ret != 0) {
			rsyserr(FERROR, errno,
				"failed to set socket option %s", tok);
		}
	}

	free(options);
}