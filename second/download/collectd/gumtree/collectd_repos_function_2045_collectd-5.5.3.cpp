static int conntrack_read (void)
{
	value_t conntrack, conntrack_max, conntrack_pct;
	FILE *fh;
	char buffer[64];
	size_t buffer_len;

	fh = fopen (old_files?CONNTRACK_FILE_OLD:CONNTRACK_FILE, "r");
	if (fh == NULL)
		return (-1);

	memset (buffer, 0, sizeof (buffer));
	if (fgets (buffer, sizeof (buffer), fh) == NULL)
	{
		fclose (fh);
		return (-1);
	}
	fclose (fh);

	/* strip trailing newline. */
	buffer_len = strlen (buffer);
	while ((buffer_len > 0) && isspace ((int) buffer[buffer_len - 1]))
	{
		buffer[buffer_len - 1] = 0;
		buffer_len--;
	}

	if (parse_value (buffer, &conntrack, DS_TYPE_GAUGE) != 0)
		return (-1);

	conntrack_submit ("conntrack", NULL, conntrack);

	fh = fopen (old_files?CONNTRACK_MAX_FILE_OLD:CONNTRACK_MAX_FILE, "r");
	if (fh == NULL)
		return (-1);

	memset (buffer, 0, sizeof (buffer));
	if (fgets (buffer, sizeof (buffer), fh) == NULL)
	{
		fclose (fh);
		return (-1);
	}
	fclose (fh);

	/* strip trailing newline. */
	buffer_len = strlen (buffer);
	while ((buffer_len > 0) && isspace ((int) buffer[buffer_len - 1]))
	{
		buffer[buffer_len - 1] = 0;
		buffer_len--;
	}

	if (parse_value (buffer, &conntrack_max, DS_TYPE_GAUGE) != 0)
		return (-1);

	conntrack_submit ("conntrack", "max", conntrack_max);
	conntrack_pct.gauge = (conntrack.gauge / conntrack_max.gauge) * 100;
	conntrack_submit ("percent", "used", conntrack_pct);


	return (0);
}