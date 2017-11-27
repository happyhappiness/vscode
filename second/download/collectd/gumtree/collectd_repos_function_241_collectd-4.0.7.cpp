int check_create_dir (const char *file_orig)
{
	struct stat statbuf;

	char  file_copy[512];
	char  dir[512];
	int   dir_len = 512;
	char *fields[16];
	int   fields_num;
	char *ptr;
	char *saveptr;
	int   last_is_file = 1;
	int   path_is_absolute = 0;
	int   len;
	int   i;

	/*
	 * Sanity checks first
	 */
	if (file_orig == NULL)
		return (-1);

	if ((len = strlen (file_orig)) < 1)
		return (-1);
	else if (len >= 512)
		return (-1);

	/*
	 * If `file_orig' ends in a slash the last component is a directory,
	 * otherwise it's a file. Act accordingly..
	 */
	if (file_orig[len - 1] == '/')
		last_is_file = 0;
	if (file_orig[0] == '/')
		path_is_absolute = 1;

	/*
	 * Create a copy for `strtok_r' to destroy
	 */
	strncpy (file_copy, file_orig, 512);
	file_copy[511] = '\0';

	/*
	 * Break into components. This will eat up several slashes in a row and
	 * remove leading and trailing slashes..
	 */
	ptr = file_copy;
	saveptr = NULL;
	fields_num = 0;
	while ((fields[fields_num] = strtok_r (ptr, "/", &saveptr)) != NULL)
	{
		ptr = NULL;
		fields_num++;

		if (fields_num >= 16)
			break;
	}

	/*
	 * For each component, do..
	 */
	for (i = 0; i < (fields_num - last_is_file); i++)
	{
		/*
		 * Do not create directories that start with a dot. This
		 * prevents `../../' attacks and other likely malicious
		 * behavior.
		 */
		if (fields[i][0] == '.')
		{
			ERROR ("Cowardly refusing to create a directory that begins with a `.' (dot): `%s'", file_orig);
			return (-2);
		}

		/*
		 * Join the components together again
		 */
		dir[0] = '/';
		if (strjoin (dir + path_is_absolute, dir_len - path_is_absolute,
					fields, i + 1, "/") < 0)
		{
			ERROR ("strjoin failed: `%s', component #%i", file_orig, i);
			return (-1);
		}

		if (stat (dir, &statbuf) == -1)
		{
			if (errno == ENOENT)
			{
				if (mkdir (dir, 0755) == -1)
				{
					char errbuf[1024];
					ERROR ("mkdir (%s): %s", dir,
							sstrerror (errno,
								errbuf, sizeof (errbuf)));
					return (-1);
				}
			}
			else
			{
				char errbuf[1024];
				ERROR ("stat (%s): %s", dir,
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				return (-1);
			}
		}
		else if (!S_ISDIR (statbuf.st_mode))
		{
			ERROR ("stat (%s): Not a directory!", dir);
			return (-1);
		}
	}

	return (0);
}