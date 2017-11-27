			break;

	return (ret);
}

/*
 * Returns true if the plugin is loaded (i.e. `exists') and false otherwise.
 * This is used in `configfile.c' to skip sections that are not needed..
 */
int plugin_exists (char *type)
{
	if (plugin_search (type) == NULL)
		return (0);
	else
		return (1);
}

/*
 * (Try to) load the shared object `file'. Won't complain if it isn't a shared
 * object, but it will bitch about a shared object not having a
 * ``module_register'' symbol..
 */
int plugin_load_file (char *file)
{
	lt_dlhandle dlh;
	void (*reg_handle) (void);

	lt_dlinit ();
	lt_dlerror (); /* clear errors */

	if ((dlh = lt_dlopen (file)) == NULL)
		return (1);

	if ((reg_handle = lt_dlsym (dlh, "module_register")) == NULL)
	{
		syslog (LOG_WARNING, "Couldn't find symbol ``module_register'' in ``%s'': %s\n",
				file, lt_dlerror ());
		lt_dlclose (dlh);
		return (-1);
	}

	(*reg_handle) ();

	return (0);
}

#define BUFSIZE 512
int plugin_load (const char *type)
{
	DIR  *dh;
	char *dir;
	char  filename[BUFSIZE];
	char  typename[BUFSIZE];
	int   typename_len;
	int   ret;
	struct stat    statbuf;
	struct dirent *de;

	dir = plugin_get_dir ();
	ret = 1;

	/* don't load twice */
	if (plugin_search (type) != NULL)
		return (0);

	/* `cpu' should not match `cpufreq'. To solve this we add `.so' to the
	 * type when matching the filename */
	if (snprintf (typename, BUFSIZE, "%s.so", type) >= BUFSIZE)
	{
		syslog (LOG_WARNING, "snprintf: truncated: `%s.so'", type);
		return (-1);
	}
	typename_len = strlen (typename);

	if ((dh = opendir (dir)) == NULL)
	{
		syslog (LOG_ERR, "opendir (%s): %s", dir, strerror (errno));
		return (-1);
	}

	while ((de = readdir (dh)) != NULL)
	{
		if (strncasecmp (de->d_name, typename, typename_len))
			continue;

		if (snprintf (filename, BUFSIZE, "%s/%s", dir, de->d_name) >= BUFSIZE)
		{
			syslog (LOG_WARNING, "snprintf: truncated: `%s/%s'", dir, de->d_name);
			continue;
		}

		if (lstat (filename, &statbuf) == -1)
		{
			syslog (LOG_WARNING, "stat %s: %s", filename, strerror (errno));
			continue;
		}
		else if (!S_ISREG (statbuf.st_mode))
		{
			/* don't follow symlinks */
			continue;
		}

		if (plugin_load_file (filename) == 0)
		{
			/* success */
			ret = 0;
			break;
		}
	}

	closedir (dh);

	return (ret);
}

/*
 * (Try to) load all plugins in `dir'. Returns the number of loaded plugins..
 */
int plugin_load_all (char *dir)
{
	DIR *dh;
	struct dirent *de;
	char filename[BUFSIZE];
	struct stat statbuf;

	if (dir == NULL)
		dir = plugin_get_dir ();
	else
		plugin_set_dir (dir);

	if ((dh = opendir (dir)) == NULL)
	{
		syslog (LOG_ERR, "opendir (%s): %s", dir, strerror (errno));
		return (0);
	}

	while ((de = readdir (dh)) != NULL)
	{
		if (snprintf (filename, BUFSIZE, "%s/%s", dir, de->d_name) >= BUFSIZE)
		{
			syslog (LOG_WARNING, "snprintf: truncated: %s/%s", dir, de->d_name);
			continue;
		}

		if (lstat (filename, &statbuf) == -1)
		{
			syslog (LOG_WARNING, "stat %s: %s", filename, strerror (errno));
			continue;
		}
		else if (!S_ISREG (statbuf.st_mode))
		{
			continue;
		}

		plugin_load_file (filename);
	}

	closedir (dh);

	return (plugin_count ());
}
