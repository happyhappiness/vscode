		long int tmp = strtol (value, NULL, 0);

		if (tmp < 1) {
			fprintf (stderr, "email plugin: `MaxConns' was set to invalid "
					"value %li, will use default %i.\n",
					tmp, MAX_CONNS);
			ERROR ("email plugin: `MaxConns' was set to invalid "
					"value %li, will use default %i.\n",
					tmp, MAX_CONNS);
			max_conns = MAX_CONNS;
		}
		else if (tmp > MAX_CONNS_LIMIT) {
			fprintf (stderr, "email plugin: `MaxConns' was set to invalid "
					"value %li, will use hardcoded limit %i.\n",
					tmp, MAX_CONNS_LIMIT);
			ERROR ("email plugin: `MaxConns' was set to invalid "
					"value %li, will use hardcoded limit %i.\n",
					tmp, MAX_CONNS_LIMIT);
			max_conns = MAX_CONNS_LIMIT;
		}
		else {
			max_conns = (int)tmp;
		}
	}
