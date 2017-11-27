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
	size_t len;

	/*
	 * Sanity checks first
	 */
	if (file_orig == NULL)
		return (-1);

	if ((len = strlen (file_orig)) < 1)
		return (-1);
	else if (len >= sizeof (file_copy))
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
	sstrncpy (file_copy, file_orig, sizeof (file_copy));

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
	for (int i = 0; i < (fields_num - last_is_file); i++)
	{
		/*
		 * Do not create directories that start with a dot. This
		 * prevents `../../' attacks and other likely malicious
		 * behavior.
		 */
		if (fields[i][0] == '.')
		{
			ERROR ("Cowardly refusing to create a directory that "
					"begins with a `.' (dot): `%s'", file_orig);
			return (-2);
		}

		/*
		 * Join the components together again
		 */
		dir[0] = '/';
		if (strjoin (dir + path_is_absolute, (size_t) (dir_len - path_is_absolute),
					fields, (size_t) (i + 1), "/") < 0)
		{
			ERROR ("strjoin failed: `%s', component #%i", file_orig, i);
			return (-1);
		}

		while (42) {
			if ((stat (dir, &statbuf) == -1)
					&& (lstat (dir, &statbuf) == -1))
			{
				if (errno == ENOENT)
				{
					if (mkdir (dir, S_IRWXU | S_IRWXG | S_IRWXO) == 0)
						break;

					/* this might happen, if a different thread created
					 * the directory in the meantime
					 * => call stat() again to check for S_ISDIR() */
					if (EEXIST == errno)
						continue;

					char errbuf[1024];
					ERROR ("check_create_dir: mkdir (%s): %s", dir,
							sstrerror (errno,
								errbuf, sizeof (errbuf)));
					return (-1);
				}
				else
				{
					char errbuf[1024];
					ERROR ("check_create_dir: stat (%s): %s", dir,
							sstrerror (errno, errbuf,
								sizeof (errbuf)));
					return (-1);
				}
			}
			else if (!S_ISDIR (statbuf.st_mode))
			{
				ERROR ("check_create_dir: `%s' exists but is not "
						"a directory!", dir);
				return (-1);
			}
			break;
		}
	}

	return (0);
}