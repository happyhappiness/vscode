static int entropy_read (void)
{
	double entropy;
	FILE *fh;
	char buffer[64];

	fh = fopen (ENTROPY_FILE, "r");
	if (fh == NULL)
		return (-1);

	if (fgets (buffer, sizeof (buffer), fh) == NULL)
	{
		fclose (fh);
		return (-1);
	}
	fclose (fh);

	entropy = atof (buffer);
	
	if (entropy > 0.0)
		entropy_submit (entropy);

	return (0);
}