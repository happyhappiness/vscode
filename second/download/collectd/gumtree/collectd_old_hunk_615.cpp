
static c_avl_tree_t *data_sets;

static char *plugindir = NULL;

#ifndef DEFAULT_MAX_READ_INTERVAL
# define DEFAULT_MAX_READ_INTERVAL TIME_T_TO_CDTIME_T (86400)
#endif
static c_heap_t       *read_heap = NULL;
static llist_t        *read_list;
static int             read_loop = 1;
static pthread_mutex_t read_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  read_cond = PTHREAD_COND_INITIALIZER;
static pthread_t      *read_threads = NULL;
static int             read_threads_num = 0;
static cdtime_t        max_read_interval = DEFAULT_MAX_READ_INTERVAL;

static write_queue_t  *write_queue_head;
static write_queue_t  *write_queue_tail;
static long            write_queue_length = 0;
static _Bool           write_loop = 1;
static pthread_mutex_t write_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t  write_cond = PTHREAD_COND_INITIALIZER;
static pthread_t      *write_threads = NULL;
static size_t          write_threads_num = 0;

static pthread_key_t   plugin_ctx_key;
static _Bool           plugin_ctx_key_initialized = 0;

static long            write_limit_high = 0;
static long            write_limit_low = 0;

static derive_t        stats_values_dropped = 0;
static _Bool           record_statistics = 0;

/*
 * Static functions
 */
static int plugin_dispatch_values_internal (value_list_t *vl);

static const char *plugin_get_dir (void)
{
	if (plugindir == NULL)
		return (PLUGINDIR);
	else
		return (plugindir);
}

static void plugin_update_internal_statistics (void) { /* {{{ */
	derive_t copy_write_queue_length;
	value_list_t vl = VALUE_LIST_INIT;
	value_t values[2];

	copy_write_queue_length = write_queue_length;

	/* Initialize `vl' */
	vl.values = values;
	vl.values_len = 2;
	vl.time = 0;
	sstrncpy (vl.host, hostname_g, sizeof (vl.host));
	sstrncpy (vl.plugin, "collectd", sizeof (vl.plugin));

	vl.type_instance[0] = 0;
	vl.values_len = 1;

	/* Write queue */
	sstrncpy (vl.plugin_instance, "write_queue",
			sizeof (vl.plugin_instance));

	/* Write queue : queue length */
	vl.values[0].gauge = (gauge_t) copy_write_queue_length;
	sstrncpy (vl.type, "queue_length", sizeof (vl.type));
	vl.type_instance[0] = 0;
	plugin_dispatch_values (&vl);

	/* Write queue : Values dropped (queue length > low limit) */
	vl.values[0].derive = (derive_t) stats_values_dropped;
	sstrncpy (vl.type, "derive", sizeof (vl.type));
	sstrncpy (vl.type_instance, "dropped", sizeof (vl.type_instance));
	plugin_dispatch_values (&vl);

	/* Cache */
	sstrncpy (vl.plugin_instance, "cache",
			sizeof (vl.plugin_instance));

	/* Cache : Nb entry in cache tree */
	vl.values[0].gauge = (gauge_t) uc_get_size();
	sstrncpy (vl.type, "cache_size", sizeof (vl.type));
	vl.type_instance[0] = 0;
	plugin_dispatch_values (&vl);

	return;
} /* }}} void plugin_update_internal_statistics */

static void destroy_callback (callback_func_t *cf) /* {{{ */
{
	if (cf == NULL)
		return;

	if ((cf->cf_udata.data != NULL) && (cf->cf_udata.free_func != NULL))
	{
		cf->cf_udata.free_func (cf->cf_udata.data);
		cf->cf_udata.data = NULL;
		cf->cf_udata.free_func = NULL;
	}
	sfree (cf);
} /* }}} void destroy_callback */

static void destroy_all_callbacks (llist_t **list) /* {{{ */
{
	llentry_t *le;

	if (*list == NULL)
		return;

	le = llist_head (*list);
	while (le != NULL)
	{
		llentry_t *le_next;

		le_next = le->next;

		sfree (le->key);
		destroy_callback (le->value);
		le->value = NULL;

		le = le_next;
	}

	llist_destroy (*list);
	*list = NULL;
} /* }}} void destroy_all_callbacks */

static void destroy_read_heap (void) /* {{{ */
{
	if (read_heap == NULL)
		return;

	while (42)
	{
		read_func_t *rf;

		rf = c_heap_get_root (read_heap);
		if (rf == NULL)
			break;
		sfree (rf->rf_name);
		destroy_callback ((callback_func_t *) rf);
	}

	c_heap_destroy (read_heap);
	read_heap = NULL;
} /* }}} void destroy_read_heap */

static int register_callback (llist_t **list, /* {{{ */
		const char *name, callback_func_t *cf)
{
	llentry_t *le;
	char *key;

	if (*list == NULL)
	{
		*list = llist_create ();
		if (*list == NULL)
		{
			ERROR ("plugin: register_callback: "
					"llist_create failed.");
			destroy_callback (cf);
			return (-1);
		}
	}

	key = strdup (name);
	if (key == NULL)
	{
		ERROR ("plugin: register_callback: strdup failed.");
		destroy_callback (cf);
		return (-1);
	}

	le = llist_search (*list, name);
	if (le == NULL)
	{
		le = llentry_create (key, cf);
		if (le == NULL)
		{
			ERROR ("plugin: register_callback: "
					"llentry_create failed.");
			sfree (key);
			destroy_callback (cf);
			return (-1);
		}

		llist_append (*list, le);
	}
	else
	{
		callback_func_t *old_cf;

		old_cf = le->value;
		le->value = cf;

		WARNING ("plugin: register_callback: "
				"a callback named `%s' already exists - "
				"overwriting the old entry!", name);

		destroy_callback (old_cf);
		sfree (key);
	}

	return (0);
} /* }}} int register_callback */

static void log_list_callbacks (llist_t **list, /* {{{ */
				const char *comment)
{
	char *str;
	int len;
	int i;
	llentry_t *le;
	int n;
	char **keys;

	n = llist_size(*list);
	if (n == 0)
	{
		INFO("%s [none]", comment);
		return;
	}

	keys = calloc(n, sizeof(char*));

	if (keys == NULL)
	{
		ERROR("%s: failed to allocate memory for list of callbacks",
		      comment);

		return;
	}

	for (le = llist_head (*list), i = 0, len = 0;
	     le != NULL;
	     le = le->next, i++)
	{
		keys[i] = le->key;
		len += strlen(le->key) + 6;
	}
	str = malloc(len + 10);
	if (str == NULL)
	{
		ERROR("%s: failed to allocate memory for list of callbacks",
		      comment);
	}
	else
	{
		*str = '\0';
		strjoin(str, len, keys, n, "', '");
		INFO("%s ['%s']", comment, str);
		sfree (str);
	}
	sfree (keys);
} /* }}} void log_list_callbacks */

static int create_register_callback (llist_t **list, /* {{{ */
		const char *name, void *callback, user_data_t const *ud)
{
	callback_func_t *cf;

	cf = calloc (1, sizeof (*cf));
	if (cf == NULL)
	{
		ERROR ("plugin: create_register_callback: calloc failed.");
		return (-1);
	}

	cf->cf_callback = callback;
	if (ud == NULL)
	{
		cf->cf_udata.data = NULL;
		cf->cf_udata.free_func = NULL;
	}
	else
	{
		cf->cf_udata = *ud;
	}

	cf->cf_ctx = plugin_get_ctx ();

	return (register_callback (list, name, cf));
} /* }}} int create_register_callback */

static int plugin_unregister (llist_t *list, const char *name) /* {{{ */
{
	llentry_t *e;

	if (list == NULL)
		return (-1);

	e = llist_search (list, name);
	if (e == NULL)
		return (-1);

	llist_remove (list, e);

	sfree (e->key);
	destroy_callback (e->value);

	llentry_destroy (e);

	return (0);
} /* }}} int plugin_unregister */

/*
 * (Try to) load the shared object `file'. Won't complain if it isn't a shared
 * object, but it will bitch about a shared object not having a
 * ``module_register'' symbol..
 */
static int plugin_load_file (char *file, uint32_t flags)
{
	lt_dlhandle dlh;
	void (*reg_handle) (void);

	lt_dlinit ();
	lt_dlerror (); /* clear errors */

#if LIBTOOL_VERSION == 2
	if (flags & PLUGIN_FLAGS_GLOBAL) {
		lt_dladvise advise;
		lt_dladvise_init(&advise);
		lt_dladvise_global(&advise);
		dlh = lt_dlopenadvise(file, advise);
		lt_dladvise_destroy(&advise);
	} else {
		dlh = lt_dlopen (file);
	}
#else /* if LIBTOOL_VERSION == 1 */
	if (flags & PLUGIN_FLAGS_GLOBAL)
		WARNING ("plugin_load_file: The global flag is not supported, "
				"libtool 2 is required for this.");
	dlh = lt_dlopen (file);
#endif

	if (dlh == NULL)
	{
		char errbuf[1024] = "";

		ssnprintf (errbuf, sizeof (errbuf),
				"lt_dlopen (\"%s\") failed: %s. "
				"The most common cause for this problem is "
				"missing dependencies. Use ldd(1) to check "
				"the dependencies of the plugin "
				"/ shared object.",
				file, lt_dlerror ());

		ERROR ("%s", errbuf);
		/* Make sure this is printed to STDERR in any case, but also
		 * make sure it's printed only once. */
		if (list_log != NULL)
			fprintf (stderr, "ERROR: %s\n", errbuf);

		return (1);
	}

	if ((reg_handle = (void (*) (void)) lt_dlsym (dlh, "module_register")) == NULL)
	{
		WARNING ("Couldn't find symbol \"module_register\" in \"%s\": %s\n",
				file, lt_dlerror ());
		lt_dlclose (dlh);
		return (-1);
	}

	(*reg_handle) ();

	return (0);
}

static void *plugin_read_thread (void __attribute__((unused)) *args)
{
	while (read_loop != 0)
	{
		read_func_t *rf;
		plugin_ctx_t old_ctx;
		cdtime_t start;
		cdtime_t now;
		cdtime_t elapsed;
		int status;
		int rf_type;
		int rc;

		/* Get the read function that needs to be read next.
		 * We don't need to hold "read_lock" for the heap, but we need
		 * to call c_heap_get_root() and pthread_cond_wait() in the
		 * same protected block. */
		pthread_mutex_lock (&read_lock);
		rf = c_heap_get_root (read_heap);
		if (rf == NULL)
		{
			pthread_cond_wait (&read_cond, &read_lock);
                        pthread_mutex_unlock (&read_lock);
			continue;
		}
		pthread_mutex_unlock (&read_lock);

		if (rf->rf_interval == 0)
		{
			/* this should not happen, because the interval is set
			 * for each plugin when loading it
			 * XXX: issue a warning? */
			rf->rf_interval = plugin_get_interval ();
			rf->rf_effective_interval = rf->rf_interval;

			rf->rf_next_read = cdtime ();
		}

		/* sleep until this entry is due,
		 * using pthread_cond_timedwait */
		pthread_mutex_lock (&read_lock);
		/* In pthread_cond_timedwait, spurious wakeups are possible
		 * (and really happen, at least on NetBSD with > 1 CPU), thus
		 * we need to re-evaluate the condition every time
		 * pthread_cond_timedwait returns. */
		rc = 0;
		while ((read_loop != 0)
				&& (cdtime () < rf->rf_next_read)
				&& rc == 0)
		{
			struct timespec ts = { 0 };

			CDTIME_T_TO_TIMESPEC (rf->rf_next_read, &ts);

			rc = pthread_cond_timedwait (&read_cond, &read_lock,
				&ts);
		}

		/* Must hold `read_lock' when accessing `rf->rf_type'. */
		rf_type = rf->rf_type;
		pthread_mutex_unlock (&read_lock);

		/* Check if we're supposed to stop.. This may have interrupted
		 * the sleep, too. */
		if (read_loop == 0)
		{
			/* Insert `rf' again, so it can be free'd correctly */
			c_heap_insert (read_heap, rf);
			break;
		}

		/* The entry has been marked for deletion. The linked list
		 * entry has already been removed by `plugin_unregister_read'.
		 * All we have to do here is free the `read_func_t' and
		 * continue. */
		if (rf_type == RF_REMOVE)
		{
			DEBUG ("plugin_read_thread: Destroying the `%s' "
					"callback.", rf->rf_name);
			sfree (rf->rf_name);
			destroy_callback ((callback_func_t *) rf);
			rf = NULL;
			continue;
		}

		DEBUG ("plugin_read_thread: Handling `%s'.", rf->rf_name);

		start = cdtime ();

		old_ctx = plugin_set_ctx (rf->rf_ctx);

		if (rf_type == RF_SIMPLE)
		{
			int (*callback) (void);

			callback = rf->rf_callback;
			status = (*callback) ();
		}
		else
		{
			plugin_read_cb callback;

			assert (rf_type == RF_COMPLEX);

			callback = rf->rf_callback;
			status = (*callback) (&rf->rf_udata);
		}

		plugin_set_ctx (old_ctx);

		/* If the function signals failure, we will increase the
		 * intervals in which it will be called. */
		if (status != 0)
		{
			rf->rf_effective_interval *= 2;
			if (rf->rf_effective_interval > max_read_interval)
				rf->rf_effective_interval = max_read_interval;

			NOTICE ("read-function of plugin `%s' failed. "
					"Will suspend it for %.3f seconds.",
					rf->rf_name,
					CDTIME_T_TO_DOUBLE (rf->rf_effective_interval));
		}
		else
		{
			/* Success: Restore the interval, if it was changed. */
			rf->rf_effective_interval = rf->rf_interval;
		}

		/* update the ``next read due'' field */
		now = cdtime ();

		/* calculate the time spent in the read function */
		elapsed = (now - start);

		if (elapsed > rf->rf_effective_interval)
			WARNING ("plugin_read_thread: read-function of the `%s' plugin took %.3f "
				"seconds, which is above its read interval (%.3f seconds). You might "
				"want to adjust the `Interval' or `ReadThreads' settings.",
				rf->rf_name, CDTIME_T_TO_DOUBLE(elapsed),
				CDTIME_T_TO_DOUBLE(rf->rf_effective_interval));

		DEBUG ("plugin_read_thread: read-function of the `%s' plugin took "
				"%.6f seconds.",
				rf->rf_name, CDTIME_T_TO_DOUBLE(elapsed));

		DEBUG ("plugin_read_thread: Effective interval of the "
				"`%s' plugin is %.3f seconds.",
				rf->rf_name,
				CDTIME_T_TO_DOUBLE (rf->rf_effective_interval));

		/* Calculate the next (absolute) time at which this function
		 * should be called. */
		rf->rf_next_read += rf->rf_effective_interval;

		/* Check, if `rf_next_read' is in the past. */
		if (rf->rf_next_read < now)
		{
			/* `rf_next_read' is in the past. Insert `now'
			 * so this value doesn't trail off into the
			 * past too much. */
			rf->rf_next_read = now;
		}

		DEBUG ("plugin_read_thread: Next read of the `%s' plugin at %.3f.",
				rf->rf_name,
				CDTIME_T_TO_DOUBLE (rf->rf_next_read));

		/* Re-insert this read function into the heap again. */
		c_heap_insert (read_heap, rf);
	} /* while (read_loop) */

	pthread_exit (NULL);
	return ((void *) 0);
} /* void *plugin_read_thread */

static void start_read_threads (int num)
{
	if (read_threads != NULL)
		return;

	read_threads = (pthread_t *) calloc (num, sizeof (pthread_t));
	if (read_threads == NULL)
	{
		ERROR ("plugin: start_read_threads: calloc failed.");
		return;
	}

	read_threads_num = 0;
	for (int i = 0; i < num; i++)
	{
		if (pthread_create (read_threads + read_threads_num, NULL,
					plugin_read_thread, NULL) == 0)
		{
			read_threads_num++;
		}
		else
		{
			ERROR ("plugin: start_read_threads: pthread_create failed.");
			return;
		}
	} /* for (i) */
} /* void start_read_threads */

static void stop_read_threads (void)
{
	if (read_threads == NULL)
		return;

	INFO ("collectd: Stopping %i read threads.", read_threads_num);

	pthread_mutex_lock (&read_lock);
	read_loop = 0;
	DEBUG ("plugin: stop_read_threads: Signalling `read_cond'");
	pthread_cond_broadcast (&read_cond);
	pthread_mutex_unlock (&read_lock);

	for (int i = 0; i < read_threads_num; i++)
	{
		if (pthread_join (read_threads[i], NULL) != 0)
		{
			ERROR ("plugin: stop_read_threads: pthread_join failed.");
		}
		read_threads[i] = (pthread_t) 0;
	}
	sfree (read_threads);
	read_threads_num = 0;
} /* void stop_read_threads */

static void plugin_value_list_free (value_list_t *vl) /* {{{ */
{
	if (vl == NULL)
		return;

	meta_data_destroy (vl->meta);
	sfree (vl->values);
	sfree (vl);
} /* }}} void plugin_value_list_free */

static value_list_t *plugin_value_list_clone (value_list_t const *vl_orig) /* {{{ */
{
	value_list_t *vl;

	if (vl_orig == NULL)
		return (NULL);

	vl = malloc (sizeof (*vl));
	if (vl == NULL)
		return (NULL);
	memcpy (vl, vl_orig, sizeof (*vl));

	vl->values = calloc (vl_orig->values_len, sizeof (*vl->values));
	if (vl->values == NULL)
	{
		plugin_value_list_free (vl);
		return (NULL);
	}
	memcpy (vl->values, vl_orig->values,
			vl_orig->values_len * sizeof (*vl->values));

	vl->meta = meta_data_clone (vl->meta);
	if ((vl_orig->meta != NULL) && (vl->meta == NULL))
	{
		plugin_value_list_free (vl);
		return (NULL);
	}

	if (vl->time == 0)
		vl->time = cdtime ();

	/* Fill in the interval from the thread context, if it is zero. */
	if (vl->interval == 0)
	{
		plugin_ctx_t ctx = plugin_get_ctx ();

		if (ctx.interval != 0)
			vl->interval = ctx.interval;
		else
		{
			char name[6 * DATA_MAX_NAME_LEN];
			FORMAT_VL (name, sizeof (name), vl);
			ERROR ("plugin_value_list_clone: Unable to determine "
					"interval from context for "
					"value list \"%s\". "
					"This indicates a broken plugin. "
					"Please report this problem to the "
					"collectd mailing list or at "
					"<http://collectd.org/bugs/>.", name);
			vl->interval = cf_get_default_interval ();
		}
	}

	return (vl);
} /* }}} value_list_t *plugin_value_list_clone */

static int plugin_write_enqueue (value_list_t const *vl) /* {{{ */
{
	write_queue_t *q;

	q = malloc (sizeof (*q));
	if (q == NULL)
		return (ENOMEM);
	q->next = NULL;

	q->vl = plugin_value_list_clone (vl);
	if (q->vl == NULL)
	{
		sfree (q);
		return (ENOMEM);
	}

	/* Store context of caller (read plugin); otherwise, it would not be
	 * available to the write plugins when actually dispatching the
	 * value-list later on. */
	q->ctx = plugin_get_ctx ();

	pthread_mutex_lock (&write_lock);

	if (write_queue_tail == NULL)
	{
		write_queue_head = q;
		write_queue_tail = q;
		write_queue_length = 1;
	}
	else
	{
		write_queue_tail->next = q;
		write_queue_tail = q;
		write_queue_length += 1;
	}

	pthread_cond_signal (&write_cond);
	pthread_mutex_unlock (&write_lock);

	return (0);
} /* }}} int plugin_write_enqueue */

static value_list_t *plugin_write_dequeue (void) /* {{{ */
{
	write_queue_t *q;
	value_list_t *vl;

	pthread_mutex_lock (&write_lock);

	while (write_loop && (write_queue_head == NULL))
		pthread_cond_wait (&write_cond, &write_lock);

	if (write_queue_head == NULL)
	{
		pthread_mutex_unlock (&write_lock);
		return (NULL);
	}

	q = write_queue_head;
	write_queue_head = q->next;
	write_queue_length -= 1;
	if (write_queue_head == NULL) {
		write_queue_tail = NULL;
		assert(0 == write_queue_length);
		}

	pthread_mutex_unlock (&write_lock);

	(void) plugin_set_ctx (q->ctx);

	vl = q->vl;
	sfree (q);
	return (vl);
} /* }}} value_list_t *plugin_write_dequeue */

static void *plugin_write_thread (void __attribute__((unused)) *args) /* {{{ */
{
	while (write_loop)
	{
		value_list_t *vl = plugin_write_dequeue ();
		if (vl == NULL)
			continue;

		plugin_dispatch_values_internal (vl);

		plugin_value_list_free (vl);
	}

	pthread_exit (NULL);
	return ((void *) 0);
} /* }}} void *plugin_write_thread */

static void start_write_threads (size_t num) /* {{{ */
{
	if (write_threads != NULL)
		return;

	write_threads = (pthread_t *) calloc (num, sizeof (pthread_t));
	if (write_threads == NULL)
	{
		ERROR ("plugin: start_write_threads: calloc failed.");
		return;
	}

	write_threads_num = 0;
	for (size_t i = 0; i < num; i++)
	{
		int status;

		status = pthread_create (write_threads + write_threads_num,
				/* attr = */ NULL,
				plugin_write_thread,
				/* arg = */ NULL);
		if (status != 0)
		{
			char errbuf[1024];
			ERROR ("plugin: start_write_threads: pthread_create failed "
					"with status %i (%s).", status,
					sstrerror (status, errbuf, sizeof (errbuf)));
			return;
		}

		write_threads_num++;
	} /* for (i) */
} /* }}} void start_write_threads */

static void stop_write_threads (void) /* {{{ */
{
	write_queue_t *q;
	size_t i;

	if (write_threads == NULL)
		return;

	INFO ("collectd: Stopping %zu write threads.", write_threads_num);

	pthread_mutex_lock (&write_lock);
	write_loop = 0;
	DEBUG ("plugin: stop_write_threads: Signalling `write_cond'");
	pthread_cond_broadcast (&write_cond);
	pthread_mutex_unlock (&write_lock);

	for (i = 0; i < write_threads_num; i++)
	{
		if (pthread_join (write_threads[i], NULL) != 0)
		{
			ERROR ("plugin: stop_write_threads: pthread_join failed.");
		}
		write_threads[i] = (pthread_t) 0;
	}
	sfree (write_threads);
	write_threads_num = 0;

	pthread_mutex_lock (&write_lock);
	i = 0;
	for (q = write_queue_head; q != NULL; )
	{
		write_queue_t *q1 = q;
		plugin_value_list_free (q->vl);
		q = q->next;
		sfree (q1);
		i++;
	}
	write_queue_head = NULL;
	write_queue_tail = NULL;
	write_queue_length = 0;
	pthread_mutex_unlock (&write_lock);

	if (i > 0)
	{
		WARNING ("plugin: %zu value list%s left after shutting down "
				"the write threads.",
				i, (i == 1) ? " was" : "s were");
	}
} /* }}} void stop_write_threads */

/*
 * Public functions
 */
void plugin_set_dir (const char *dir)
{
	sfree (plugindir);

	if (dir == NULL)
	{
		plugindir = NULL;
		return;
	}

	plugindir = strdup (dir);
	if (plugindir == NULL)
		ERROR ("plugin_set_dir: strdup(\"%s\") failed", dir);
}

static _Bool plugin_is_loaded (char const *name)
{
	int status;

	if (plugins_loaded == NULL)
		plugins_loaded = c_avl_create ((int (*) (const void *, const void *)) strcasecmp);
	assert (plugins_loaded != NULL);

	status = c_avl_get (plugins_loaded, name, /* ret_value = */ NULL);
	return (status == 0);
}

static int plugin_mark_loaded (char const *name)
{
	char *name_copy;
	int status;

	name_copy = strdup (name);
	if (name_copy == NULL)
		return (ENOMEM);

	status = c_avl_insert (plugins_loaded,
			/* key = */ name_copy, /* value = */ NULL);
	return (status);
}

static void plugin_free_loaded (void)
{
	void *key;
	void *value;

	if (plugins_loaded == NULL)
		return;

	while (c_avl_pick (plugins_loaded, &key, &value) == 0)
	{
		sfree (key);
		assert (value == NULL);
	}

	c_avl_destroy (plugins_loaded);
	plugins_loaded = NULL;
}

#define BUFSIZE 512
int plugin_load (char const *plugin_name, uint32_t flags)
{
	DIR  *dh;
	const char *dir;
	char  filename[BUFSIZE] = "";
	char  typename[BUFSIZE];
	int   ret;
	struct stat    statbuf;
	struct dirent *de;
	int status;

	if (plugin_name == NULL)
		return (EINVAL);

	/* Check if plugin is already loaded and don't do anything in this
	 * case. */
	if (plugin_is_loaded (plugin_name))
		return (0);

	dir = plugin_get_dir ();
	ret = 1;

	/*
	 * XXX: Magic at work:
	 *
	 * Some of the language bindings, for example the Python and Perl
	 * plugins, need to be able to export symbols to the scripts they run.
	 * For this to happen, the "Globals" flag needs to be set.
	 * Unfortunately, this technical detail is hard to explain to the
	 * average user and she shouldn't have to worry about this, ideally.
	 * So in order to save everyone's sanity use a different default for a
	 * handful of special plugins. --octo
	 */
	if ((strcasecmp ("perl", plugin_name) == 0)
			|| (strcasecmp ("python", plugin_name) == 0))
		flags |= PLUGIN_FLAGS_GLOBAL;

	/* `cpu' should not match `cpufreq'. To solve this we add `.so' to the
	 * type when matching the filename */
	status = ssnprintf (typename, sizeof (typename), "%s.so", plugin_name);
	if ((status < 0) || ((size_t) status >= sizeof (typename)))
	{
		WARNING ("plugin_load: Filename too long: \"%s.so\"", plugin_name);
		return (-1);
	}

	if ((dh = opendir (dir)) == NULL)
	{
		char errbuf[1024];
		ERROR ("plugin_load: opendir (%s) failed: %s", dir,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	while ((de = readdir (dh)) != NULL)
	{
		if (strcasecmp (de->d_name, typename))
			continue;

		status = ssnprintf (filename, sizeof (filename),
				"%s/%s", dir, de->d_name);
		if ((status < 0) || ((size_t) status >= sizeof (filename)))
		{
			WARNING ("plugin_load: Filename too long: \"%s/%s\"",
					dir, de->d_name);
			continue;
		}

		if (lstat (filename, &statbuf) == -1)
		{
			char errbuf[1024];
			WARNING ("plugin_load: stat (\"%s\") failed: %s",
					filename,
					sstrerror (errno, errbuf, sizeof (errbuf)));
			continue;
		}
		else if (!S_ISREG (statbuf.st_mode))
		{
			/* don't follow symlinks */
			WARNING ("plugin_load: %s is not a regular file.",
				       	filename);
			continue;
		}

		status = plugin_load_file (filename, flags);
		if (status == 0)
		{
			/* success */
			plugin_mark_loaded (plugin_name);
			ret = 0;
			INFO ("plugin_load: plugin \"%s\" successfully loaded.", plugin_name);
			break;
		}
		else
		{
			ERROR ("plugin_load: Load plugin \"%s\" failed with "
					"status %i.", plugin_name, status);
		}
	}

	closedir (dh);

	if (filename[0] == 0)
		ERROR ("plugin_load: Could not find plugin \"%s\" in %s",
				plugin_name, dir);

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

int plugin_register_complex_config (const char *type,
		int (*callback) (oconfig_item_t *))
{
	return (cf_register_complex (type, callback));
} /* int plugin_register_complex_config */

int plugin_register_init (const char *name,
		int (*callback) (void))
{
	return (create_register_callback (&list_init, name, (void *) callback,
				/* user_data = */ NULL));
} /* plugin_register_init */

static int plugin_compare_read_func (const void *arg0, const void *arg1)
{
	const read_func_t *rf0;
	const read_func_t *rf1;

	rf0 = arg0;
	rf1 = arg1;

	if (rf0->rf_next_read < rf1->rf_next_read)
		return (-1);
	else if (rf0->rf_next_read > rf1->rf_next_read)
		return (1);
	else
		return (0);
} /* int plugin_compare_read_func */

/* Add a read function to both, the heap and a linked list. The linked list if
 * used to look-up read functions, especially for the remove function. The heap
 * is used to determine which plugin to read next. */
static int plugin_insert_read (read_func_t *rf)
{
	int status;
	llentry_t *le;

	rf->rf_next_read = cdtime ();
	rf->rf_effective_interval = rf->rf_interval;

	pthread_mutex_lock (&read_lock);

	if (read_list == NULL)
	{
		read_list = llist_create ();
		if (read_list == NULL)
		{
			pthread_mutex_unlock (&read_lock);
			ERROR ("plugin_insert_read: read_list failed.");
			return (-1);
		}
	}

	if (read_heap == NULL)
	{
		read_heap = c_heap_create (plugin_compare_read_func);
		if (read_heap == NULL)
		{
			pthread_mutex_unlock (&read_lock);
			ERROR ("plugin_insert_read: c_heap_create failed.");
			return (-1);
		}
	}

	le = llist_search (read_list, rf->rf_name);
	if (le != NULL)
	{
		pthread_mutex_unlock (&read_lock);
		WARNING ("The read function \"%s\" is already registered. "
				"Check for duplicate \"LoadPlugin\" lines "
				"in your configuration!",
				rf->rf_name);
		return (EINVAL);
	}

	le = llentry_create (rf->rf_name, rf);
	if (le == NULL)
	{
		pthread_mutex_unlock (&read_lock);
		ERROR ("plugin_insert_read: llentry_create failed.");
		return (-1);
	}

	status = c_heap_insert (read_heap, rf);
	if (status != 0)
	{
		pthread_mutex_unlock (&read_lock);
		ERROR ("plugin_insert_read: c_heap_insert failed.");
		llentry_destroy (le);
		return (-1);
	}

	/* This does not fail. */
	llist_append (read_list, le);

	/* Wake up all the read threads. */
	pthread_cond_broadcast (&read_cond);
	pthread_mutex_unlock (&read_lock);
	return (0);
} /* int plugin_insert_read */

int plugin_register_read (const char *name,
		int (*callback) (void))
{
	read_func_t *rf;
	int status;

	rf = calloc (1, sizeof (*rf));
	if (rf == NULL)
	{
		ERROR ("plugin_register_read: calloc failed.");
		return (ENOMEM);
	}

	rf->rf_callback = (void *) callback;
	rf->rf_udata.data = NULL;
	rf->rf_udata.free_func = NULL;
	rf->rf_ctx = plugin_get_ctx ();
	rf->rf_group[0] = '\0';
	rf->rf_name = strdup (name);
	rf->rf_type = RF_SIMPLE;
	rf->rf_interval = plugin_get_interval ();

	status = plugin_insert_read (rf);
	if (status != 0) {
		sfree (rf->rf_name);
		sfree (rf);
	}

	return (status);
} /* int plugin_register_read */

int plugin_register_complex_read (const char *group, const char *name,
		plugin_read_cb callback,
		cdtime_t interval,
		user_data_t const *user_data)
{
	read_func_t *rf;
	int status;

	rf = calloc (1,sizeof (*rf));
	if (rf == NULL)
	{
		ERROR ("plugin_register_complex_read: calloc failed.");
		return (ENOMEM);
	}

	rf->rf_callback = (void *) callback;
	if (group != NULL)
		sstrncpy (rf->rf_group, group, sizeof (rf->rf_group));
	else
		rf->rf_group[0] = '\0';
	rf->rf_name = strdup (name);
	rf->rf_type = RF_COMPLEX;
	rf->rf_interval = (interval != 0) ? interval : plugin_get_interval ();

	/* Set user data */
	if (user_data == NULL)
	{
		rf->rf_udata.data = NULL;
		rf->rf_udata.free_func = NULL;
	}
	else
	{
		rf->rf_udata = *user_data;
	}

	rf->rf_ctx = plugin_get_ctx ();

	status = plugin_insert_read (rf);
	if (status != 0) {
		sfree (rf->rf_name);
		sfree (rf);
	}

	return (status);
} /* int plugin_register_complex_read */

int plugin_register_write (const char *name,
		plugin_write_cb callback, user_data_t const *ud)
{
	return (create_register_callback (&list_write, name,
				(void *) callback, ud));
} /* int plugin_register_write */

static int plugin_flush_timeout_callback (user_data_t *ud)
{
	flush_callback_t *cb = ud->data;

	return plugin_flush (cb->name, cb->timeout, /* identifier = */ NULL);
} /* static int plugin_flush_callback */

static void plugin_flush_timeout_callback_free (void *data)
{
	flush_callback_t *cb = data;

	if (cb == NULL) return;

	sfree (cb->name);
	sfree (cb);
} /* static void plugin_flush_callback_free */

static char *plugin_flush_callback_name (const char *name)
{
	const char *flush_prefix = "flush/";
	size_t prefix_size;
	char *flush_name;
	size_t name_size;

	prefix_size = strlen(flush_prefix);
	name_size = strlen(name);

	flush_name = malloc (name_size + prefix_size + 1);
	if (flush_name == NULL)
	{
		ERROR ("plugin_flush_callback_name: malloc failed.");
		return (NULL);
	}

	sstrncpy (flush_name, flush_prefix, prefix_size + 1);
	sstrncpy (flush_name + prefix_size, name, name_size + 1);

	return flush_name;
} /* static char *plugin_flush_callback_name */

int plugin_register_flush (const char *name,
		plugin_flush_cb callback, user_data_t const *ud)
{
	int status;
	plugin_ctx_t ctx = plugin_get_ctx ();

	status = create_register_callback (&list_flush, name,
		(void *) callback, ud);
	if (status != 0)
		return status;

	if (ctx.flush_interval != 0)
	{
		char *flush_name;
		flush_callback_t *cb;

		flush_name = plugin_flush_callback_name (name);
		if (flush_name == NULL)
			return (-1);

		cb = malloc(sizeof (*cb));
		if (cb == NULL)
		{
			ERROR ("plugin_register_flush: malloc failed.");
			sfree (flush_name);
			return (-1);
		}

		cb->name = strdup (name);
		if (cb->name == NULL)
		{
			ERROR ("plugin_register_flush: strdup failed.");
			sfree (cb);
			sfree (flush_name);
			return (-1);
		}
		cb->timeout = ctx.flush_timeout;

		status = plugin_register_complex_read (
			/* group     = */ "flush",
			/* name      = */ flush_name,
			/* callback  = */ plugin_flush_timeout_callback,
			/* interval  = */ ctx.flush_interval,
			/* user data = */ &(user_data_t) {
				.data = cb,
				.free_func = plugin_flush_timeout_callback_free,
			});

		sfree (flush_name);
		if (status != 0)
		{
			sfree (cb->name);
			sfree (cb);
			return status;
		}
	}

	return 0;
} /* int plugin_register_flush */

int plugin_register_missing (const char *name,
		plugin_missing_cb callback, user_data_t const *ud)
{
	return (create_register_callback (&list_missing, name,
				(void *) callback, ud));
} /* int plugin_register_missing */

int plugin_register_shutdown (const char *name,
		int (*callback) (void))
{
	return (create_register_callback (&list_shutdown, name,
				(void *) callback, /* user_data = */ NULL));
} /* int plugin_register_shutdown */

static void plugin_free_data_sets (void)
{
	void *key;
	void *value;

	if (data_sets == NULL)
		return;

	while (c_avl_pick (data_sets, &key, &value) == 0)
	{
		data_set_t *ds = value;
		/* key is a pointer to ds->type */

		sfree (ds->ds);
		sfree (ds);
	}

	c_avl_destroy (data_sets);
	data_sets = NULL;
} /* void plugin_free_data_sets */

int plugin_register_data_set (const data_set_t *ds)
{
	data_set_t *ds_copy;

	if ((data_sets != NULL)
			&& (c_avl_get (data_sets, ds->type, NULL) == 0))
	{
		NOTICE ("Replacing DS `%s' with another version.", ds->type);
		plugin_unregister_data_set (ds->type);
	}
	else if (data_sets == NULL)
	{
		data_sets = c_avl_create ((int (*) (const void *, const void *)) strcmp);
		if (data_sets == NULL)
			return (-1);
	}

	ds_copy = malloc (sizeof (*ds_copy));
	if (ds_copy == NULL)
		return (-1);
	memcpy(ds_copy, ds, sizeof (data_set_t));

	ds_copy->ds = malloc (sizeof (*ds_copy->ds)
			* ds->ds_num);
	if (ds_copy->ds == NULL)
	{
		sfree (ds_copy);
		return (-1);
	}

	for (size_t i = 0; i < ds->ds_num; i++)
		memcpy (ds_copy->ds + i, ds->ds + i, sizeof (data_source_t));

	return (c_avl_insert (data_sets, (void *) ds_copy->type, (void *) ds_copy));
} /* int plugin_register_data_set */

int plugin_register_log (const char *name,
		plugin_log_cb callback, user_data_t const *ud)
{
	return (create_register_callback (&list_log, name,
				(void *) callback, ud));
} /* int plugin_register_log */

int plugin_register_notification (const char *name,
		plugin_notification_cb callback, user_data_t const *ud)
{
	return (create_register_callback (&list_notification, name,
				(void *) callback, ud));
} /* int plugin_register_log */

int plugin_unregister_config (const char *name)
{
	cf_unregister (name);
	return (0);
} /* int plugin_unregister_config */

int plugin_unregister_complex_config (const char *name)
{
	cf_unregister_complex (name);
	return (0);
} /* int plugin_unregister_complex_config */

int plugin_unregister_init (const char *name)
{
	return (plugin_unregister (list_init, name));
}

int plugin_unregister_read (const char *name) /* {{{ */
{
	llentry_t *le;
	read_func_t *rf;

	if (name == NULL)
		return (-ENOENT);

	pthread_mutex_lock (&read_lock);

	if (read_list == NULL)
	{
		pthread_mutex_unlock (&read_lock);
		return (-ENOENT);
	}

	le = llist_search (read_list, name);
	if (le == NULL)
	{
		pthread_mutex_unlock (&read_lock);
		WARNING ("plugin_unregister_read: No such read function: %s",
				name);
		return (-ENOENT);
	}

	llist_remove (read_list, le);

	rf = le->value;
	assert (rf != NULL);
	rf->rf_type = RF_REMOVE;

	pthread_mutex_unlock (&read_lock);

	llentry_destroy (le);

	DEBUG ("plugin_unregister_read: Marked `%s' for removal.", name);

	return (0);
} /* }}} int plugin_unregister_read */

void plugin_log_available_writers (void)
{
	log_list_callbacks (&list_write, "Available write targets:");
}

static int compare_read_func_group (llentry_t *e, void *ud) /* {{{ */
{
	read_func_t *rf    = e->value;
	char        *group = ud;

	return strcmp (rf->rf_group, (const char *)group);
} /* }}} int compare_read_func_group */

int plugin_unregister_read_group (const char *group) /* {{{ */
{
	llentry_t *le;
	read_func_t *rf;

	int found = 0;

	if (group == NULL)
		return (-ENOENT);

	pthread_mutex_lock (&read_lock);

	if (read_list == NULL)
	{
		pthread_mutex_unlock (&read_lock);
		return (-ENOENT);
	}

	while (42)
	{
		le = llist_search_custom (read_list,
				compare_read_func_group, (void *)group);

		if (le == NULL)
			break;

		++found;

		llist_remove (read_list, le);

		rf = le->value;
		assert (rf != NULL);
		rf->rf_type = RF_REMOVE;

		llentry_destroy (le);

		DEBUG ("plugin_unregister_read_group: "
				"Marked `%s' (group `%s') for removal.",
				rf->rf_name, group);
	}

	pthread_mutex_unlock (&read_lock);

	if (found == 0)
	{
		WARNING ("plugin_unregister_read_group: No such "
				"group of read function: %s", group);
		return (-ENOENT);
	}

	return (0);
} /* }}} int plugin_unregister_read_group */

int plugin_unregister_write (const char *name)
{
	return (plugin_unregister (list_write, name));
}

int plugin_unregister_flush (const char *name)
{
	plugin_ctx_t ctx = plugin_get_ctx ();

	if (ctx.flush_interval != 0)
	{
		char *flush_name;

		flush_name = plugin_flush_callback_name (name);
		if (flush_name != NULL)
		{
			plugin_unregister_read(flush_name);
			sfree (flush_name);
		}
	}

	return plugin_unregister (list_flush, name);
}

int plugin_unregister_missing (const char *name)
{
	return (plugin_unregister (list_missing, name));
}

int plugin_unregister_shutdown (const char *name)
{
	return (plugin_unregister (list_shutdown, name));
}

int plugin_unregister_data_set (const char *name)
{
	data_set_t *ds;

	if (data_sets == NULL)
		return (-1);

	if (c_avl_remove (data_sets, name, NULL, (void *) &ds) != 0)
		return (-1);

	sfree (ds->ds);
	sfree (ds);

	return (0);
} /* int plugin_unregister_data_set */

int plugin_unregister_log (const char *name)
{
	return (plugin_unregister (list_log, name));
}

int plugin_unregister_notification (const char *name)
{
	return (plugin_unregister (list_notification, name));
}

int plugin_init_all (void)
{
	char const *chain_name;
	llentry_t *le;
	int status;
	int ret = 0;

	/* Init the value cache */
	uc_init ();

	if (IS_TRUE (global_option_get ("CollectInternalStats")))
		record_statistics = 1;

	chain_name = global_option_get ("PreCacheChain");
	pre_cache_chain = fc_chain_get_by_name (chain_name);

	chain_name = global_option_get ("PostCacheChain");
	post_cache_chain = fc_chain_get_by_name (chain_name);

	write_limit_high = global_option_get_long ("WriteQueueLimitHigh",
			/* default = */ 0);
	if (write_limit_high < 0)
	{
		ERROR ("WriteQueueLimitHigh must be positive or zero.");
		write_limit_high = 0;
	}

	write_limit_low = global_option_get_long ("WriteQueueLimitLow",
			/* default = */ write_limit_high / 2);
	if (write_limit_low < 0)
	{
		ERROR ("WriteQueueLimitLow must be positive or zero.");
		write_limit_low = write_limit_high / 2;
	}
	else if (write_limit_low > write_limit_high)
	{
		ERROR ("WriteQueueLimitLow must not be larger than "
				"WriteQueueLimitHigh.");
		write_limit_low = write_limit_high;
	}

	write_threads_num = global_option_get_long ("WriteThreads",
			/* default = */ 5);
	if (write_threads_num < 1)
	{
		ERROR ("WriteThreads must be positive.");
		write_threads_num = 5;
	}

	if ((list_init == NULL) && (read_heap == NULL))
		return ret;

	/* Calling all init callbacks before checking if read callbacks
	 * are available allows the init callbacks to register the read
	 * callback. */
	le = llist_head (list_init);
	while (le != NULL)
	{
		callback_func_t *cf;
		plugin_init_cb callback;
		plugin_ctx_t old_ctx;

		cf = le->value;
		old_ctx = plugin_set_ctx (cf->cf_ctx);
		callback = cf->cf_callback;
		status = (*callback) ();
		plugin_set_ctx (old_ctx);

		if (status != 0)
		{
			ERROR ("Initialization of plugin `%s' "
					"failed with status %i. "
					"Plugin will be unloaded.",
					le->key, status);
			/* Plugins that register read callbacks from the init
			 * callback should take care of appropriate error
			 * handling themselves. */
			/* FIXME: Unload _all_ functions */
			plugin_unregister_read (le->key);
			ret = -1;
		}

		le = le->next;
	}

	start_write_threads ((size_t) write_threads_num);

	max_read_interval = global_option_get_time ("MaxReadInterval",
			DEFAULT_MAX_READ_INTERVAL);

	/* Start read-threads */
	if (read_heap != NULL)
	{
		const char *rt;
		int num;

		rt = global_option_get ("ReadThreads");
		num = atoi (rt);
		if (num != -1)
			start_read_threads ((num > 0) ? num : 5);
	}
	return ret;
} /* void plugin_init_all */

/* TODO: Rename this function. */
void plugin_read_all (void)
{
	if(record_statistics) {
		plugin_update_internal_statistics ();
	}
	uc_check_timeout ();

	return;
} /* void plugin_read_all */

/* Read function called when the `-T' command line argument is given. */
int plugin_read_all_once (void)
{
	int status;
	int return_status = 0;

	if (read_heap == NULL)
	{
		NOTICE ("No read-functions are registered.");
		return (0);
	}

	while (42)
	{
		read_func_t *rf;
		plugin_ctx_t old_ctx;

		rf = c_heap_get_root (read_heap);
		if (rf == NULL)
			break;

		old_ctx = plugin_set_ctx (rf->rf_ctx);

		if (rf->rf_type == RF_SIMPLE)
		{
			int (*callback) (void);

			callback = rf->rf_callback;
			status = (*callback) ();
		}
		else
		{
			plugin_read_cb callback;

			callback = rf->rf_callback;
			status = (*callback) (&rf->rf_udata);
		}

		plugin_set_ctx (old_ctx);

		if (status != 0)
		{
			NOTICE ("read-function of plugin `%s' failed.",
					rf->rf_name);
			return_status = -1;
		}

		sfree (rf->rf_name);
		destroy_callback ((void *) rf);
	}

	return (return_status);
} /* int plugin_read_all_once */

int plugin_write (const char *plugin, /* {{{ */
		const data_set_t *ds, const value_list_t *vl)
{
  llentry_t *le;
  int status;

  if (vl == NULL)
    return (EINVAL);

  if (list_write == NULL)
    return (ENOENT);

  if (ds == NULL)
  {
    ds = plugin_get_ds (vl->type);
    if (ds == NULL)
    {
      ERROR ("plugin_write: Unable to lookup type `%s'.", vl->type);
      return (ENOENT);
    }
  }

  if (plugin == NULL)
  {
    int success = 0;
    int failure = 0;

    le = llist_head (list_write);
    while (le != NULL)
    {
      callback_func_t *cf = le->value;
      plugin_write_cb callback;

      /* do not switch plugin context; rather keep the context (interval)
       * information of the calling read plugin */

      DEBUG ("plugin: plugin_write: Writing values via %s.", le->key);
      callback = cf->cf_callback;
      status = (*callback) (ds, vl, &cf->cf_udata);
      if (status != 0)
        failure++;
      else
        success++;

      le = le->next;
    }

    if ((success == 0) && (failure != 0))
      status = -1;
    else
      status = 0;
  }
  else /* plugin != NULL */
  {
    callback_func_t *cf;
    plugin_write_cb callback;

    le = llist_head (list_write);
    while (le != NULL)
    {
      if (strcasecmp (plugin, le->key) == 0)
        break;

      le = le->next;
    }

    if (le == NULL)
