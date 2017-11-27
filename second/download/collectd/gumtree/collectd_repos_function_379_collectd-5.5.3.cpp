static int sysfs_file_to_buffer(char const *dir, /* {{{ */
		char const *power_supply,
		char const *basename,
		char *buffer, size_t buffer_size)
{
	int status;
	FILE *fp;
	char filename[PATH_MAX];

	ssnprintf (filename, sizeof (filename), "%s/%s/%s",
			dir, power_supply, basename);

	/* No file isn't the end of the world -- not every system will be
	 * reporting the same set of statistics */
	if (access (filename, R_OK) != 0)
		return ENOENT;

	fp = fopen (filename, "r");
	if (fp == NULL)
	{
		status = errno;
		if (status != ENOENT)
		{
			char errbuf[1024];
			WARNING ("battery plugin: fopen (%s) failed: %s", filename,
					sstrerror (status, errbuf, sizeof (errbuf)));
		}
		return status;
	}

	if (fgets (buffer, buffer_size, fp) == NULL)
	{
		status = errno;
		if (status != ENODEV)
		{
			char errbuf[1024];
			WARNING ("battery plugin: fgets (%s) failed: %s", filename,
					sstrerror (status, errbuf, sizeof (errbuf)));
		}
		fclose (fp);
		return status;
	}

	strstripnewline (buffer);

	fclose (fp);
	return 0;
}