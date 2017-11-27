static int change_basedir (const char *orig_dir)
{
	char *dir = strdup (orig_dir);
	int dirlen;
	int status;

	if (dir == NULL)
	{
		char errbuf[1024];
		ERROR ("strdup failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}
	
	dirlen = strlen (dir);
	while ((dirlen > 0) && (dir[dirlen - 1] == '/'))
		dir[--dirlen] = '\0';

	if (dirlen <= 0)
		return (-1);

	status = chdir (dir);
	free (dir);

	if (status != 0)
	{
		if (errno == ENOENT)
		{
			if (mkdir (orig_dir, 0755) == -1)
			{
				char errbuf[1024];
				ERROR ("change_basedir: mkdir (%s): %s", orig_dir,
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				return (-1);
			}
			else if (chdir (orig_dir) == -1)
			{
				char errbuf[1024];
				ERROR ("chdir (%s): %s", orig_dir,
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				return (-1);
			}
		}
		else
		{
			char errbuf[1024];
			ERROR ("chdir (%s): %s", orig_dir,
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			return (-1);
		}
	}

	return (0);
}