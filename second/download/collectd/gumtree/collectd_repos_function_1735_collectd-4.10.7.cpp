static int conntrack_read (void)
{
	value_t conntrack;
	FILE *fh;
	char buffer[64];
	size_t buffer_len;

	fh = fopen (CONNTRACK_FILE, "r");
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

	conntrack_submit (conntrack);

	return (0);
}