static int swap_read_separate (void) /* {{{ */
{
	FILE *fh;
	char buffer[1024];

	fh = fopen ("/proc/swaps", "r");
	if (fh == NULL)
	{
		char errbuf[1024];
		WARNING ("swap plugin: fopen (/proc/swaps) failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while (fgets (buffer, sizeof (buffer), fh) != NULL)
	{
		char *fields[8];
		int numfields;
		char *endptr;

		char path[PATH_MAX];
		gauge_t size;
		gauge_t used;
		gauge_t free;

		numfields = strsplit (buffer, fields, STATIC_ARRAY_SIZE (fields));
		if (numfields != 5)
			continue;

		sstrncpy (path, fields[0], sizeof (path));
		escape_slashes (path, sizeof (path));

		errno = 0;
		endptr = NULL;
		size = strtod (fields[2], &endptr);
		if ((endptr == fields[2]) || (errno != 0))
			continue;

		errno = 0;
		endptr = NULL;
		used = strtod (fields[3], &endptr);
		if ((endptr == fields[3]) || (errno != 0))
			continue;

		if (size < used)
			continue;

		free = size - used;

		swap_submit_gauge (path, "used", used);
		swap_submit_gauge (path, "free", free);
	}

	fclose (fh);

	return (0);
}