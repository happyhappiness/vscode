static int swap_read (void) /* {{{ */
{
	FILE *fh;
	char buffer[1024];

	char *fields[8];
	int numfields;

	_Bool old_kernel=0;

	derive_t swap_used   = 0;
	derive_t swap_cached = 0;
	derive_t swap_free   = 0;
	derive_t swap_total  = 0;
	derive_t swap_in     = 0;
	derive_t swap_out    = 0;

	if ((fh = fopen ("/proc/meminfo", "r")) == NULL)
	{
		char errbuf[1024];
		WARNING ("memory: fopen: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while (fgets (buffer, sizeof (buffer), fh) != NULL)
	{
		numfields = strsplit (buffer, fields, STATIC_ARRAY_SIZE (fields));
		if (numfields < 2)
			continue;

		if (strcasecmp (fields[0], "SwapTotal:") == 0)
			strtoderive (fields[1], &swap_total);
		else if (strcasecmp (fields[0], "SwapFree:") == 0)
			strtoderive (fields[1], &swap_free);
		else if (strcasecmp (fields[0], "SwapCached:") == 0)
			strtoderive (fields[1], &swap_cached);
	}

	if (fclose (fh))
	{
		char errbuf[1024];
		WARNING ("memory: fclose: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
	}

	if ((swap_free + swap_cached) > swap_total)
		return (-1);

	swap_used = swap_total - (swap_free + swap_cached);

	if ((fh = fopen ("/proc/vmstat", "r")) == NULL)
	{
		// /proc/vmstat does not exist in kernels <2.6
		if ((fh = fopen ("/proc/stat", "r")) == NULL )
		{
			char errbuf[1024];
			WARNING ("swap: fopen: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			return (-1);
		}
		else
			old_kernel = 1;
	}

	while (fgets (buffer, sizeof (buffer), fh) != NULL)
	{
		numfields = strsplit (buffer, fields, STATIC_ARRAY_SIZE (fields));

		if (!old_kernel)
		{
			if (numfields != 2)
				continue;

			if (strcasecmp ("pswpin", fields[0]) == 0)
				strtoderive (fields[1], &swap_in);
			else if (strcasecmp ("pswpout", fields[0]) == 0)
				strtoderive (fields[1], &swap_out);
		}
		else /* if (old_kernel) */
		{
			if (numfields != 3)
				continue;

			if (strcasecmp ("page", fields[0]) == 0)
			{
				strtoderive (fields[1], &swap_in);
				strtoderive (fields[2], &swap_out);
			}
		}
	} /* while (fgets) */

	if (fclose (fh))
	{
		char errbuf[1024];
		WARNING ("swap: fclose: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
	}

	swap_submit ("used",   1024 * swap_used,   DS_TYPE_GAUGE);
	swap_submit ("free",   1024 * swap_free,   DS_TYPE_GAUGE);
	swap_submit ("cached", 1024 * swap_cached, DS_TYPE_GAUGE);
	swap_submit ("in",  swap_in,  DS_TYPE_DERIVE);
	swap_submit ("out", swap_out, DS_TYPE_DERIVE);

	return (0);
}