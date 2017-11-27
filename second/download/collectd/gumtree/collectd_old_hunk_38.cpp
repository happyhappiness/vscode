			break;

	return (ret);
}

/*
 * (Try to) load the shared object `name'. Won't complain if it isn't a shared
 * object, but it will bitch about a shared object not having a
 * ``module_register'' symbol..
 */
void plugin_load (char *name)
{
	lt_dlhandle dlh;
	void (*reg_handle) (void);

	lt_dlinit ();
	lt_dlerror (); /* clear errors */

	if ((dlh = lt_dlopen (name)) == NULL)
		return;

	if ((reg_handle = lt_dlsym (dlh, "module_register")) == NULL)
	{
		syslog (LOG_WARNING, "Couldn't find symbol ``module_register'' in ``%s'': %s\n",
				name, lt_dlerror ());
		lt_dlclose (dlh);
		return;
	}

	(*reg_handle) ();
}

/*
 * (Try to) load all plugins in `dir'. Returns the number of loaded plugins..
 */
#define BUFSIZE 512
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
		fprintf (stderr, "Error: Cannot read plugin directory `%s'\n", dir);
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
