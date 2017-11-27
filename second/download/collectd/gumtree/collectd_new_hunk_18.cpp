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

#ifdef HAVE_LIBKSTAT
int get_kstat (kstat_t **ksp_ptr, char *module, int instance, char *name)
{
	char ident[128];
	
	if (kc == NULL)
