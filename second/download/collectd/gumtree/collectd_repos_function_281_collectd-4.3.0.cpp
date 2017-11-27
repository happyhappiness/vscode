static int *ps_read_tasks (int pid)
{
	int *list = NULL;
	int  list_size = 1; /* size of allocated space, in elements */
	int  list_len = 0;  /* number of currently used elements */

	char           dirname[64];
	DIR           *dh;
	struct dirent *ent;

	snprintf (dirname, 64, "/proc/%i/task", pid);
	dirname[63] = '\0';

	if ((dh = opendir (dirname)) == NULL)
	{
		DEBUG ("Failed to open directory `%s'", dirname);
		return (NULL);
	}

	while ((ent = readdir (dh)) != NULL)
	{
		if (!isdigit (ent->d_name[0]))
			continue;

		if ((list_len + 1) >= list_size)
		{
			int *new_ptr;
			int  new_size = 2 * list_size;
			/* Comes in sizes: 2, 4, 8, 16, ... */

			new_ptr = (int *) realloc (list, (size_t) (sizeof (int) * new_size));
			if (new_ptr == NULL)
			{
				if (list != NULL)
					free (list);
				ERROR ("processes plugin: "
						"Failed to allocate more memory.");
				return (NULL);
			}

			list = new_ptr;
			list_size = new_size;

			memset (list + list_len, 0, sizeof (int) * (list_size - list_len));
		}

		list[list_len] = atoi (ent->d_name);
		if (list[list_len] != 0)
			list_len++;
	}

	closedir (dh);

	if (list_len == 0)
		return (NULL);

	assert (list_len < list_size);
	assert (list[list_len] == 0);

	return (list);
}