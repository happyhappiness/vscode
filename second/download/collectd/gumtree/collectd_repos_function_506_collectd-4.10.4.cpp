static int ps_read_tasks (int pid)
{
	char           dirname[64];
	DIR           *dh;
	struct dirent *ent;
	int count = 0;

	ssnprintf (dirname, sizeof (dirname), "/proc/%i/task", pid);

	if ((dh = opendir (dirname)) == NULL)
	{
		DEBUG ("Failed to open directory `%s'", dirname);
		return (-1);
	}

	while ((ent = readdir (dh)) != NULL)
	{
		if (!isdigit ((int) ent->d_name[0]))
			continue;
		else
			count++;
	}
	closedir (dh);

	return ((count >= 1) ? count : 1);
}