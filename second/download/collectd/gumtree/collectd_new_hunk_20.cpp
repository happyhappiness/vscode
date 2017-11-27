	closedir (dh);

	return (ret);
}

/*
 * The `register_*' functions follow
 */
int plugin_register_config (const char *name,
		int (*callback) (const char *key, const char *val),
		const char **keys, int keys_num)
{
	cf_register (name, callback, keys, keys_num);
	return (0);
} /* int plugin_register_config */

int plugin_register_init (const char *name,
		int (*callback) (void))
{
	return (register_callback (&list_init, name, (void *) callback));
} /* plugin_register_init */

int plugin_register_read (const char *name,
		int (*callback) (void))
{
	read_func_t *rf;

	rf = (read_func_t *) malloc (sizeof (read_func_t));
	if (rf == NULL)
	{
		char errbuf[1024];
		ERROR ("plugin_register_read: malloc failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	memset (rf, '\0', sizeof (read_func_t));
	rf->wait_time = interval_g;
	rf->wait_left = 0;
	rf->callback = callback;
	rf->needs_read = DONE;

	return (register_callback (&list_read, name, (void *) rf));
} /* int plugin_register_read */

int plugin_register_write (const char *name,
		int (*callback) (const data_set_t *ds, const value_list_t *vl))
{
	return (register_callback (&list_write, name, (void *) callback));
} /* int plugin_register_write */

int plugin_register_shutdown (char *name,
		int (*callback) (void))
{
	return (register_callback (&list_shutdown, name, (void *) callback));
} /* int plugin_register_shutdown */

int plugin_register_data_set (const data_set_t *ds)
{
	data_set_t *ds_copy;
	int i;

	if ((list_data_set != NULL)
			&& (llist_search (list_data_set, ds->type) != NULL))
	{
		NOTICE ("Replacing DS `%s' with another version.", ds->type);
		plugin_unregister_data_set (ds->type);
	}

	ds_copy = (data_set_t *) malloc (sizeof (data_set_t));
	if (ds_copy == NULL)
		return (-1);
	memcpy(ds_copy, ds, sizeof (data_set_t));

	ds_copy->ds = (data_source_t *) malloc (sizeof (data_source_t)
			* ds->ds_num);
	if (ds_copy->ds == NULL)
	{
		free (ds_copy);
		return (-1);
	}

	for (i = 0; i < ds->ds_num; i++)
		memcpy (ds_copy->ds + i, ds->ds + i, sizeof (data_source_t));

	return (register_callback (&list_data_set, ds->type, (void *) ds_copy));
} /* int plugin_register_data_set */

int plugin_register_log (char *name,
		void (*callback) (int priority, const char *msg))
{
	return (register_callback (&list_log, name, (void *) callback));
} /* int plugin_register_log */

int plugin_unregister_config (const char *name)
{
	cf_unregister (name);
	return (0);
} /* int plugin_unregister_config */

int plugin_unregister_init (const char *name)
{
	return (plugin_unregister (list_init, name));
}

int plugin_unregister_read (const char *name)
{
	llentry_t *e;

	e = llist_search (list_read, name);

	if (e == NULL)
		return (-1);

	llist_remove (list_read, e);
	free (e->value);
	llentry_destroy (e);

	return (0);
}

int plugin_unregister_write (const char *name)
{
	return (plugin_unregister (list_write, name));
}

int plugin_unregister_shutdown (const char *name)
{
	return (plugin_unregister (list_shutdown, name));
}

int plugin_unregister_data_set (const char *name)
{
	llentry_t  *e;
	data_set_t *ds;

	if (list_data_set == NULL)
		return (-1);

	e = llist_search (list_data_set, name);

	if (e == NULL)
		return (-1);

	llist_remove (list_data_set, e);
	ds = (data_set_t *) e->value;
	llentry_destroy (e);

	sfree (ds->ds);
	sfree (ds);

	return (0);
} /* int plugin_unregister_data_set */

int plugin_unregister_log (const char *name)
{
	return (plugin_unregister (list_log, name));
}

void plugin_init_all (void)
{
	int (*callback) (void);
	llentry_t *le;
	int status;

	/* Start read-threads */
	if (list_read != NULL)
	{
		const char *rt;
		int num;
		rt = global_option_get ("ReadThreads");
		num = atoi (rt);
		start_threads ((num > 0) ? num : 5);
	}

	if (list_init == NULL)
		return;

	le = llist_head (list_init);
	while (le != NULL)
	{
		callback = (int (*) (void)) le->value;
		status = (*callback) ();

		if (status != 0)
		{
			ERROR ("Initialization of plugin `%s' "
					"failed with status %i. "
					"Plugin will be unloaded.",
					le->key, status);
			/* FIXME: Unload _all_ functions */
			plugin_unregister_read (le->key);
		}

		le = le->next;
	}
} /* void plugin_init_all */

void plugin_read_all (const int *loop)
{
	llentry_t   *le;
	read_func_t *rf;

	if (list_read == NULL)
		return;

	pthread_mutex_lock (&read_lock);

	le = llist_head (list_read);
	while (le != NULL)
	{
		rf = (read_func_t *) le->value;

		if (rf->needs_read != DONE)
		{
			le = le->next;
			continue;
		}

		if (rf->wait_left > 0)
			rf->wait_left -= interval_g;

		if (rf->wait_left <= 0)
		{
			rf->needs_read = TODO;
		}

		le = le->next;
	}

	DEBUG ("plugin: plugin_read_all: Signalling `read_cond'");
	pthread_cond_broadcast (&read_cond);
	pthread_mutex_unlock (&read_lock);
} /* void plugin_read_all */

void plugin_shutdown_all (void)
{
	int (*callback) (void);
	llentry_t *le;

	stop_threads ();

	if (list_shutdown == NULL)
		return;

	le = llist_head (list_shutdown);
	while (le != NULL)
	{
		callback = (int (*) (void)) le->value;

		/* Advance the pointer before calling the callback allows
		 * shutdown functions to unregister themselves. If done the
		 * other way around the memory `le' points to will be freed
		 * after callback returns. */
		le = le->next;

		(*callback) ();
	}
} /* void plugin_shutdown_all */

int plugin_dispatch_values (const char *name, value_list_t *vl)
{
	int (*callback) (const data_set_t *, const value_list_t *);
	data_set_t *ds;
	llentry_t *le;

	if ((list_write == NULL) || (list_data_set == NULL))
		return (-1);

	le = llist_search (list_data_set, name);
	if (le == NULL)
	{
		DEBUG ("No such dataset registered: %s", name);
		return (-1);
	}

	ds = (data_set_t *) le->value;

	DEBUG ("plugin: plugin_dispatch_values: time = %u; host = %s; "
			"plugin = %s; plugin_instance = %s; type = %s; "
			"type_instance = %s;",
			(unsigned int) vl->time, vl->host,
			vl->plugin, vl->plugin_instance,
			ds->type, vl->type_instance);

#if COLLECT_DEBUG
	assert (ds->ds_num == vl->values_len);
#else
	if (ds->ds_num != vl->values_len)
	{
		ERROR ("plugin: ds->type = %s: (ds->ds_num = %i) != "
				"(vl->values_len = %i)",
				ds->type, ds->ds_num, vl->values_len);
		return (-1);
	}
#endif

	escape_slashes (vl->host, sizeof (vl->host));
	escape_slashes (vl->plugin, sizeof (vl->plugin));
	escape_slashes (vl->plugin_instance, sizeof (vl->plugin_instance));
	escape_slashes (vl->type_instance, sizeof (vl->type_instance));

	le = llist_head (list_write);
	while (le != NULL)
	{
		callback = (int (*) (const data_set_t *, const value_list_t *)) le->value;
		(*callback) (ds, vl);

		le = le->next;
	}

	return (0);
} /* int plugin_dispatch_values */

void plugin_log (int level, const char *format, ...)
{
	char msg[512];
	va_list ap;

	void (*callback) (int, const char *);
	llentry_t *le;

	if (list_log == NULL)
		return;

#if !COLLECT_DEBUG
	if (level >= LOG_DEBUG)
		return;
#endif

	va_start (ap, format);
	vsnprintf (msg, 512, format, ap);
	msg[511] = '\0';
	va_end (ap);

	le = llist_head (list_log);
	while (le != NULL)
	{
		callback = (void (*) (int, const char *)) le->value;
		(*callback) (level, msg);

		le = le->next;
	}
} /* void plugin_log */

void plugin_complain (int level, complain_t *c, const char *format, ...)
{
	char message[512];
	va_list ap;

	if (c->delay > 0)
	{
		c->delay--;
		return;
	}

	if (c->interval < interval_g)
		c->interval = interval_g;
	else
		c->interval *= 2;

	if (c->interval > 86400)
		c->interval = 86400;

	c->delay = c->interval / interval_g;

	va_start (ap, format);
	vsnprintf (message, 512, format, ap);
	message[511] = '\0';
	va_end (ap);

	plugin_log (level, message);
}

void plugin_relief (int level, complain_t *c, const char *format, ...)
{
	char message[512];
	va_list ap;
