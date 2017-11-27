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
#undef BUFSIZE

/*
 * Call `init' on all plugins (if given)
 */
void plugin_init_all (void)
{
	plugin_t *p;

	for (p = first_plugin; p != NULL; p = p->next)
		if (p->init != NULL)
			(*p->init) ();
}

/*
 * Call `read' on all plugins (if given)
 */
void plugin_read_all (const int *loop)
{
	plugin_t *p;

	for (p = first_plugin; (*loop == 0) && (p != NULL); p = p->next)
		if (p->read != NULL)
			(*p->read) ();
}

/*
 * Call `shutdown' on all plugins (if given)
 */
void plugin_shutdown_all (void)
{
	plugin_t *p;

	for (p = first_plugin; NULL != p; p = p->next)
		if (NULL != p->shutdown)
			(*p->shutdown) ();
	return;
}

/*
 * Add plugin to the linked list of registered plugins.
 */
void plugin_register (char *type,
		void (*init) (void),
		void (*read) (void),
		void (*write) (char *, char *, char *))
{
	plugin_t *p;

	if (plugin_search (type) != NULL)
		return;

#ifdef HAVE_LIBRRD
	if (operating_mode != MODE_SERVER)
#endif
		if ((init != NULL) && (read == NULL))
			syslog (LOG_NOTICE, "Plugin `%s' doesn't provide a read function.", type);

	if ((p = (plugin_t *) malloc (sizeof (plugin_t))) == NULL)
		return;

	if ((p->type = strdup (type)) == NULL)
	{
		free (p);
		return;
	}

	p->init  = init;
	p->read  = read;
	p->write = write;

	p->shutdown = NULL;

	p->next = first_plugin;
	first_plugin = p;
}

/*
 * Register the shutdown function (optional).
 */
int plugin_register_shutdown (char *type, void (*shutdown) (void))
{
	plugin_t *p = plugin_search (type);

	if (NULL == p)
		return -1;

	p->shutdown = shutdown;
	return 0;
}

/*
 * Send received data back to the plugin/module which will append DS
 * definitions and pass it on to ``rrd_update_file''.
 */
void plugin_write (char *host, char *type, char *inst, char *val)
{
	plugin_t *p;

	if ((p = plugin_search (type)) == NULL)
		return;

	if (p->write == NULL)
		return;

	(*p->write) (host, inst, val);
}

/*
 * Receive data from the plugin/module and get it somehow to ``plugin_write'':
 * Either using ``network_send'' (when in network/client mode) or call it
 * directly (in local mode).
 */
void plugin_submit (char *type, char *inst, char *val)
{
	if (inst == NULL)
		inst = "-";

	if ((type == NULL) || (val == NULL))
	{
		DBG ("Help! NULL-pointer! type = %s; inst = %s; val = %s;",
				(type == NULL) ? "(null)" : type,
				inst,
				(val == NULL) ? "(null)" : val);
		return;
	}

        if (operating_mode == MODE_CLIENT)
		network_send (type, inst, val);
	else
		plugin_write (NULL, type, inst, val);
}

void plugin_complain (int level, complain_t *c, const char *format, ...)
{
	char message[512];
	va_list ap;
	int step;

	if (c->delay > 0)
	{
		c->delay--;
		return;
	}

	step = atoi (COLLECTD_STEP);
	assert (step > 0);

	if (c->interval < step)
		c->interval = step;
	else
		c->interval *= 2;

	if (c->interval > 86400)
		c->interval = 86400;

	c->delay = c->interval / step;

	va_start (ap, format);
	vsnprintf (message, 512, format, ap);
	message[511] = '\0';
	va_end (ap);

	syslog (level, message);
}

void plugin_relief (int level, complain_t *c, const char *format, ...)
{
	char message[512];
	va_list ap;
