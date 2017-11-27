void exit_usage (char *name)
{
	printf ("Usage: %s [OPTIONS]\n\n"
			
			"Available options:\n"
			"  General:\n"
			"    -d <dir>        Base directory to use. Default: /var/lib/collectd\n"
#if COLLECT_PING
			"  Ping:\n"
			"    -p <host>       Host to ping periodically, may be repeated to ping\n"
			"                    more than one host.\n"
#endif /* COLLECT_PING */
			"\nAvailable modules:\n"
			"  CPU:       %s\n"
			"  Disk:      %s\n"
			"  Load:      %s\n"
			"  Memory:    %s\n"
			"  Ping:      %s\n"
			"  Sensors:   %s\n"
			"  Traffic:   %s\n"
			"\n%s %s, http://verplant.org/collectd/\n"
			"by Florian octo Forster <octo@verplant.org>\n",
			PACKAGE,
			(COLLECT_CPU     ? "yes" : "no"),
			(COLLECT_DISK    ? "yes" : "no"),
			(COLLECT_LOAD    ? "yes" : "no"),
			(COLLECT_MEMORY  ? "yes" : "no"),
			(COLLECT_PING    ? "yes" : "no"),
			(COLLECT_SENSORS ? "yes" : "no"),
			(COLLECT_TRAFFIC ? "yes" : "no"),
			PACKAGE, VERSION);
	exit (0);
}

int main (int argc, char **argv)
{
	int sleepingtime;
	struct sigaction sigIntAction, sigChldAction;
	pid_t pid;
	
	memset (basedir, '\0', PATH_MAX);
	
	openlog (PACKAGE, LOG_CONS | LOG_PID, LOG_DAEMON);

	while (1)
	{
		int c;

		c = getopt (argc, argv, "d:"
#if COLLECT_PING
				"p:"
#endif /* COLLECT_PING */
				"h");

		if (c == -1)
			break;

		switch (c)
		{
			case 'd':
				if (change_basedir (optarg) != 0)
					exit (1);
				break;
#if COLLECT_PING
			case 'p':
				ping_add_host (optarg);
				break;
#endif /* COLLECT_PING */
			case 'h':
			default:
				exit_usage (argv[0]);
		}
				
	}
