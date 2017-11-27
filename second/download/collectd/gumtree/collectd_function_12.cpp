int plugin_load_all (char *dir)
{
	DIR *dh;
	struct dirent *de;
	char filename[BUFSIZE];
	struct stat statbuf;

	if (dir == NULL)
		dir = PLUGINDIR;

	if ((dh = opendir (dir)) == NULL)
	{
		fprintf (stderr, "Cannot read plugin directory `%s'\n", dir);
		return (0);
	}

	while ((de = readdir (dh)) != NULL)
	{
		if (snprintf (filename, BUFSIZE, "%s/%s", dir, de->d_name) >= BUFSIZE)
			continue;

		if (lstat (filename, &statbuf) == -1)
		{
			syslog (LOG_WARNING, "stat %s: %s", filename, strerror (errno));
			continue;
		}
		else if (!S_ISREG (statbuf.st_mode))
		{
			continue;
		}

		plugin_load (filename);
	}

	closedir (dh);

	return (plugin_count ());
}