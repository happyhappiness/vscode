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
#if COLLECT_DAEMON
	pid_t pid;
#endif

	char *configfile = CONFIGFILE;
	char *pidfile    = PIDFILE;
	char *plugindir  = PLUGINDIR;
	char *datadir    = PKGLOCALSTATEDIR;

	int daemonize = 1;

#ifdef HAVE_LIBRRD
	operating_mode = MODE_LOCAL;
#endif
	
	/* open syslog */
	openlog (PACKAGE, LOG_CONS | LOG_PID, LOG_DAEMON);

	/* read options */
	while (1)
	{
