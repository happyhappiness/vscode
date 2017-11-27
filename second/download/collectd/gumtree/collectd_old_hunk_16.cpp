			"    -f              Don't fork to the background.\n"
#endif
			"\nBuiltin defaults:\n"
			"  Config-File       "CONFIGFILE"\n"
			"  PID-File          "PIDFILE"\n"
			"  Data-Directory    "PKGLOCALSTATEDIR"\n"
#if COLLECT_DEBUG
			"  Log-File          "LOGFILE"\n"
#endif
			"  Step              "COLLECTD_STEP" seconds\n"
			"  Heartbeat         "COLLECTD_HEARTBEAT" seconds\n"
			"\n"PACKAGE" "VERSION", http://collectd.org/\n"
			"by Florian octo Forster <octo@verplant.org>\n"
			"for contributions see `AUTHORS'\n");
	exit (0);
} /* static void exit_usage (char *name) */

static int start_client (void)
{
	int step;

	struct timeval tv_now;
	struct timeval tv_next;
	struct timespec ts_wait;

	step = atoi (COLLECTD_STEP);
	if (step <= 0)
		step = 10;

#if HAVE_LIBKSTAT
	kc = NULL;
	update_kstat ();
#endif

#if HAVE_LIBSTATGRAB
	if (sg_init ())
	{
		syslog (LOG_ERR, "sg_init: %s", sg_str_error (sg_get_error ()));
		return (-1);
	}

	if (sg_drop_privileges ())
	{
		syslog (LOG_ERR, "sg_drop_privileges: %s", sg_str_error (sg_get_error ()));
		return (-1);
	}
#endif

	plugin_init_all ();

	while (loop == 0)
	{
		if (gettimeofday (&tv_next, NULL) < 0)
		{
			syslog (LOG_ERR, "gettimeofday failed: %s", strerror (errno));
			return (-1);
		}
		tv_next.tv_sec += step;

#if HAVE_LIBKSTAT
		update_kstat ();
#endif
		/* `curtime' is used by many (all?) plugins as the
		 * data-sample-time passed to RRDTool */
		curtime = time (NULL);

		/* Issue all plugins */
		plugin_read_all (&loop);

		if (gettimeofday (&tv_now, NULL) < 0)
		{
			syslog (LOG_ERR, "gettimeofday failed: %s", strerror (errno));
			return (-1);
		}

		if (timeval_sub_timespec (&tv_next, &tv_now, &ts_wait) != 0)
		{
			syslog (LOG_WARNING, "Not sleeping because `timeval_sub_timespec' returned non-zero!");
			continue;
		}

		while ((loop == 0) && (nanosleep (&ts_wait, &ts_wait) == -1))
		{
			if (errno != EINTR)
			{
				syslog (LOG_ERR, "nanosleep failed: %s", strerror (errno));
				break;
			}
		}
	}

	return (0);
} /* static int start_client (void) */

#if HAVE_LIBRRD
static int start_server (void)
{
	char *host;
	char *type;
	char *instance;
	char *values;

	int  error_counter = 0;
	int  status;

	while ((loop == 0) && (error_counter < 3))
	{
		status = network_receive (&host, &type, &instance, &values);

		if (status != 0)
		{
			if (status < 0)
				error_counter++;
			continue;
		}
		error_counter = 0;

		plugin_write (host, type, instance, values);

		if (host     != NULL) free (host);     host     = NULL;
		if (type     != NULL) free (type);     type     = NULL;
		if (instance != NULL) free (instance); instance = NULL;
		if (values   != NULL) free (values);   values   = NULL;
	}
	
	return (0);
} /* static int start_server (void) */
#endif /* HAVE_LIBRRD */

#if COLLECT_DAEMON
static int pidfile_create (const char *file)
{
	FILE *fh;

	if (file == NULL)
		file = PIDFILE;

	if ((fh = fopen (file, "w")) == NULL)
	{
		syslog (LOG_ERR, "fopen (%s): %s", file, strerror (errno));
		return (1);
	}

	fprintf (fh, "%i\n", (int) getpid ());
	fclose(fh);

	return (0);
} /* static int pidfile_create (const char *file) */
#endif /* COLLECT_DAEMON */

#if COLLECT_DAEMON
static int pidfile_remove (const char *file)
{
	if (file == NULL) {
		file = PIDFILE;
	}
	return (unlink (file));
} /* static int pidfile_remove (const char *file) */
#endif /* COLLECT_DAEMON */

int main (int argc, char **argv)
{
	struct sigaction sigIntAction;
	struct sigaction sigTermAction;
	char *datadir    = PKGLOCALSTATEDIR;
	char *configfile = CONFIGFILE;
#if COLLECT_DAEMON
	struct sigaction sigChldAction;
	char *pidfile    = NULL;
	pid_t pid;
	int daemonize    = 1;
#endif
#if COLLECT_DEBUG
	char *logfile    = LOGFILE;
#endif

#if HAVE_LIBRRD
	operating_mode = MODE_LOCAL;
#else
	operating_mode = MODE_CLIENT;
#endif

	/* open syslog */
	openlog (PACKAGE, LOG_CONS | LOG_PID, LOG_DAEMON);

	/* read options */
	while (1)
	{
		int c;

		c = getopt (argc, argv, "hC:"
#if COLLECT_DAEMON
				"fP:"
#endif
		);

		if (c == -1)
