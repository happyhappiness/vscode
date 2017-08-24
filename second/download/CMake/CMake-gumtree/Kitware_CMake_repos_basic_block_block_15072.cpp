{
		char _buffer[128];
		size_t bufsize = 128;
		char *buffer = _buffer;
		char *allocated = NULL;
		struct group	grent, *result;
		int r;

		for (;;) {
			result = &grent; /* Old getgrnam_r ignores last arg. */
			r = getgrnam_r(gname, &grent, buffer, bufsize, &result);
			if (r == 0)
				break;
			if (r != ERANGE)
				break;
			bufsize *= 2;
			free(allocated);
			allocated = malloc(bufsize);
			if (allocated == NULL)
				break;
			buffer = allocated;
		}
		if (result != NULL)
			gid = result->gr_gid;
		free(allocated);
	}