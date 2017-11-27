int walk_directory (const char *dir, dirwalk_callback_f callback,
		void *user_data)
{
	struct dirent *ent;
	DIR *dh;
	int success;
	int failure;

	success = 0;
	failure = 0;

	if ((dh = opendir (dir)) == NULL)
	{
		char errbuf[1024];
		ERROR ("walk_directory: Cannot open '%s': %s", dir,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return -1;
	}

	while ((ent = readdir (dh)) != NULL)
	{
		int status;

		if (ent->d_name[0] == '.')
			continue;

		status = (*callback) (dir, ent->d_name, user_data);
		if (status != 0)
			failure++;
		else
			success++;
	}

	closedir (dh);

	if ((success == 0) && (failure > 0))
		return (-1);
	return (0);
}