int plugin_load (const char *type, uint32_t flags)
{
	DIR  *dh;
	const char *dir;
	char  filename[BUFSIZE] = "";
	char  typename[BUFSIZE];
	int   typename_len;
	int   ret;
	struct stat    statbuf;
	struct dirent *de;
	int status;

	DEBUG ("type = %s", type);

	dir = plugin_get_dir ();
	ret = 1;

	/* `cpu' should not match `cpufreq'. To solve this we add `.so' to the
	 * type when matching the filename */
	status = ssnprintf (typename, sizeof (typename), "%s.so", type);
	if ((status < 0) || ((size_t) status >= sizeof (typename)))
	{
		WARNING ("snprintf: truncated: `%s.so'", type);
		return (-1);
	}
	typename_len = strlen (typename);

	if ((dh = opendir (dir)) == NULL)
	{
		char errbuf[1024];
		ERROR ("opendir (%s): %s", dir,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while ((de = readdir (dh)) != NULL)
	{
		if (strncasecmp (de->d_name, typename, typename_len))
			continue;

		status = ssnprintf (filename, sizeof (filename),
				"%s/%s", dir, de->d_name);
		if ((status < 0) || ((size_t) status >= sizeof (filename)))
		{
			WARNING ("snprintf: truncated: `%s/%s'", dir, de->d_name);
			continue;
		}

		if (lstat (filename, &statbuf) == -1)
		{
			char errbuf[1024];
			WARNING ("stat %s: %s", filename,
					sstrerror (errno, errbuf, sizeof (errbuf)));
			continue;
		}
		else if (!S_ISREG (statbuf.st_mode))
		{
			/* don't follow symlinks */
			WARNING ("stat %s: not a regular file", filename);
			continue;
		}

		if (plugin_load_file (filename, flags) == 0)
		{
			/* success */
			ret = 0;
			break;
		}
		else
		{
			fprintf (stderr, "Unable to load plugin %s.\n", type);
		}
	}

	closedir (dh);

	if (filename[0] == '\0')
		fprintf (stderr, "Could not find plugin %s.\n", type);

	return (ret);
}