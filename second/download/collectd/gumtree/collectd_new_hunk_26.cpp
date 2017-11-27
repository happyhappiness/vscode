		if (instance != NULL) free (instance); instance = NULL;
		if (values   != NULL) free (values);   values   = NULL;
	}
	
	return (0);
}
#endif /* HAVE_LIBRRD */

int pidfile_create (void)
{
	FILE *fh;

	if ((fh = fopen (PIDFILE, "w")) == NULL)
	{
		syslog (LOG_ERR, "fopen (pidfile): %s", strerror (errno));
		return (1);
	}

	fprintf (fh, "%d\n", getpid());
	fclose(fh);

	return (0);
}

int pidfile_remove (void)
{
      return (unlink (PIDFILE));
}

int main (int argc, char **argv)
{
	struct sigaction sigIntAction, sigChldAction;
	pid_t pid;

	char *plugindir = NULL;
	char *basedir = "/var/lib/collectd";

	int daemonize = 1;

#ifdef HAVE_LIBRRD
	operating_mode = MODE_LOCAL;
#endif
	
	/*
	 * open syslog
	 */
	openlog (PACKAGE, LOG_CONS | LOG_PID, LOG_DAEMON);

