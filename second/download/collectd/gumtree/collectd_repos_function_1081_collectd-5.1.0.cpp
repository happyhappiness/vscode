static int swap_read_combined (void) /* {{{ */
{
	FILE *fh;
	char buffer[1024];

	uint8_t have_data = 0;
	gauge_t swap_used   = 0.0;
	gauge_t swap_cached = 0.0;
	gauge_t swap_free   = 0.0;
	gauge_t swap_total  = 0.0;

	fh = fopen ("/proc/meminfo", "r");
	if (fh == NULL)
	{
		char errbuf[1024];
		WARNING ("swap plugin: fopen (/proc/meminfo) failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while (fgets (buffer, sizeof (buffer), fh) != NULL)
	{
		char *fields[8];
		int numfields;

		numfields = strsplit (buffer, fields, STATIC_ARRAY_SIZE (fields));
		if (numfields < 2)
			continue;

		if (strcasecmp (fields[0], "SwapTotal:") == 0)
		{
			swap_total = strtod (fields[1], /* endptr = */ NULL);
			have_data |= 0x01;
		}
		else if (strcasecmp (fields[0], "SwapFree:") == 0)
		{
			swap_free = strtod (fields[1], /* endptr = */ NULL);
			have_data |= 0x02;
		}
		else if (strcasecmp (fields[0], "SwapCached:") == 0)
		{
			swap_cached = strtod (fields[1], /* endptr = */ NULL);
			have_data |= 0x04;
		}
	}

	fclose (fh);

	if (have_data != 0x07)
		return (ENOENT);

	if (isnan (swap_total)
			|| (swap_total <= 0.0)
			|| ((swap_free + swap_cached) > swap_total))
		return (EINVAL);

	swap_used = swap_total - (swap_free + swap_cached);

	swap_submit_gauge (NULL, "used",   1024.0 * swap_used);
	swap_submit_gauge (NULL, "free",   1024.0 * swap_free);
	swap_submit_gauge (NULL, "cached", 1024.0 * swap_cached);

	return (0);
}