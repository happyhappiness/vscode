static int conntrack_read (void)
{
	double conntrack;
	FILE *fh;
	char buffer[64];

	fh = fopen (CONNTRACK_FILE, "r");
	if (fh == NULL)
		return (-1);

	if (fgets (buffer, sizeof (buffer), fh) == NULL)
	{
		fclose (fh);
		return (-1);
	}
	fclose (fh);

	conntrack = atof (buffer);

	if (conntrack > 0.0)
		conntrack_submit (conntrack);

	return (0);
}