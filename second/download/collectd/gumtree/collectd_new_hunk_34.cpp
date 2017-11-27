	}

	fprintf (fh, "%d\n", getpid());
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
#if COLLECT_DAEMON
	struct sigaction sigChldAction;
	pid_t pid;
#endif

	char *configfile = CONFIGFILE;
	char *pidfile    = PIDFILE;
	char *plugindir  = PLUGINDIR;
	char *datadir    = PKGLOCALSTATEDIR;

	int daemonize = 1;

#if HAVE_LIBRRD
	operating_mode = MODE_LOCAL;
#endif

	/* open syslog */
	openlog (PACKAGE, LOG_CONS | LOG_PID, LOG_DAEMON);

	/* read options */
	while (1)
	{
