			"    -f              Don't fork to the background.\n"
#endif
			"\nBuiltin defaults:\n"
			"  Config-File       "CONFIGFILE"\n"
			"  PID-File          "PIDFILE"\n"
			"  Data-Directory    "PKGLOCALSTATEDIR"\n"
			"\n"PACKAGE" "VERSION", http://collectd.org/\n"
			"by Florian octo Forster <octo@verplant.org>\n"
			"for contributions see `AUTHORS'\n");
	exit (0);
} /* static void exit_usage (char *name) */

static int do_init (void)
{
#if HAVE_LIBKSTAT
	kc = NULL;
	update_kstat ();
#endif

#if HAVE_LIBSTATGRAB
	if (sg_init ())
	{
		ERROR ("sg_init: %s", sg_str_error (sg_get_error ()));
		return (-1);
	}

	if (sg_drop_privileges ())
	{
		ERROR ("sg_drop_privileges: %s", sg_str_error (sg_get_error ()));
		return (-1);
	}
#endif

	read_types_list ();
	plugin_init_all ();

	return (0);
} /* int do_init () */


static int do_loop (void)
{
	struct timeval tv_now;
	struct timeval tv_next;
	struct timespec ts_wait;

	while (loop == 0)
	{
		if (gettimeofday (&tv_next, NULL) < 0)
		{
			char errbuf[1024];
			ERROR ("gettimeofday failed: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			return (-1);
		}
		tv_next.tv_sec += interval_g;

#if HAVE_LIBKSTAT
		update_kstat ();
#endif

		/* Issue all plugins */
		plugin_read_all (&loop);

		if (gettimeofday (&tv_now, NULL) < 0)
		{
			char errbuf[1024];
			ERROR ("gettimeofday failed: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			return (-1);
		}

		if (timeval_sub_timespec (&tv_next, &tv_now, &ts_wait) != 0)
		{
			WARNING ("Not sleeping because "
					"`timeval_sub_timespec' returned "
					"non-zero!");
			continue;
		}

		while ((loop == 0) && (nanosleep (&ts_wait, &ts_wait) == -1))
		{
			if (errno != EINTR)
			{
				char errbuf[1024];
				ERROR ("nanosleep failed: %s",
						sstrerror (errno, errbuf,
							sizeof (errbuf)));
				return (-1);
			}
		}
	} /* while (loop == 0) */

	DEBUG ("return (0);");
	return (0);
} /* int do_loop */

static int do_shutdown (void)
{
	plugin_shutdown_all ();
	return (0);
} /* int do_shutdown */

#if COLLECT_DAEMON
static int pidfile_create (void)
{
	FILE *fh;
	const char *file = global_option_get ("PIDFile");

	if ((fh = fopen (file, "w")) == NULL)
	{
		char errbuf[1024];
		ERROR ("fopen (%s): %s", file,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (1);
	}

	fprintf (fh, "%i\n", (int) getpid ());
	fclose(fh);

	return (0);
} /* static int pidfile_create (const char *file) */

static int pidfile_remove (void)
{
	const char *file = global_option_get ("PIDFile");

	DEBUG ("unlink (%s)", (file != NULL) ? file : "<null>");
	return (unlink (file));
} /* static int pidfile_remove (const char *file) */
#endif /* COLLECT_DAEMON */

int main (int argc, char **argv)
{
	struct sigaction sigIntAction;
	struct sigaction sigTermAction;
	char *configfile = CONFIGFILE;
	int test_config  = 0;
	const char *basedir;
#if COLLECT_DAEMON
	struct sigaction sigChldAction;
	pid_t pid;
	int daemonize    = 1;
#endif

	/* read options */
	while (1)
	{
		int c;

		c = getopt (argc, argv, "htC:"
#if COLLECT_DAEMON
				"fP:"
#endif
		);

		if (c == -1)
