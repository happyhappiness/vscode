void exit_usage (char *name)
{
	printf ("Usage: %s [OPTIONS]\n\n"
			
			"Available options:\n"
			"  General:\n"
			"    -d <dir>        Base directory to use\n"
			"                    Default: /var/lib/collectd\n\n"

#if COLLECT_CPU
			"  CPU:\n"
			"    -c <file>       RRD filename-template for CPU accounting\n"
			"                    Default: cpu%%d.rrd\n\n"
#endif
#if COLLECT_DISK
			"  Diskstats:\n"
			"    -k <file>       RRD filename-template for disk accounting\n"
			"                    Default: disk-%%s.rrd\n"
			"    -K <file>       RRD filename-template for partition accounting\n"
			"                    Default: partition-%%s.rrd\n\n"
#endif /* COLLECT_DISK */
#if COLLECT_LOAD
			"  Load:\n"
			"    -l <file>       RRD file for load accounting\n"
			"                    Default: load.rrd\n\n"
#endif
#if COLLECT_MEMORY
			"  Memory:\n"
			"    -m <file>       RRD file for memory accounting\n"
			"                    Default: meminfo.rrd\n\n"
#endif /* COLLECT_MEMORY */
#if COLLECT_PING
			"  Ping:\n"
			"    -p <file>       RRD file for ping accounting\n"
			"                    Default: ping.rrd\n"
			"    -P <host>       Host to ping periodically\n"
			"                    Default: default gateway\n\n"
#endif /* COLLECT_PING */
#if COLLECT_SENSORS
			"  Sensors:\n"
			"    -s <file>       RRD filename-template for lm_sensors accounting\n"
			"                    Default: sensors-%%s.rrd\n\n"
#endif
#if COLLECT_TRAFFIC
			"  Traffic:\n"
			"    -t <file>       RRD filename-template for traffic accounting\n"
			"                    Default: traffic-%%s.rrd\n\n"
#endif
			
			"%s %s, http://verplant.org/collectd/\n"
			"by Florian octo Forster <octo@verplant.org>\n",
			PACKAGE, PACKAGE, VERSION);
	exit (0);
}

int main (int argc, char **argv)
{
	int sleepingtime;
	struct sigaction sigIntAction, sigChldAction;
	pid_t pid;
	
#if COLLECT_CPU
	char *cpu_file = NULL;
#endif
#if COLLECT_DISK
	char *disk_file = NULL;
	char *partition_file = NULL;
#endif
#if COLLECT_LOAD
	char *load_file = NULL;
#endif
#if COLLECT_MEMORY
	char *mem_file = NULL;
#endif /* COLLECT_MEMORY */
#if COLLECT_PING
	char *ping_file = NULL;
	char *ping_host = NULL;
#endif /* COLLECT_PING */
#if COLLECT_TRAFFIC
	char *traffic_file = NULL;
	char *traffic_device = NULL;
#endif
#if COLLECT_SENSORS
	char *sensors_file = NULL;
#endif

	memset (basedir, '\0', PATH_MAX);
	
	openlog (PACKAGE, LOG_CONS | LOG_PID, LOG_DAEMON);

	while (1)
	{
		int c;

		c = getopt (argc, argv, "d:"
#if COLLECT_CPU
				"c:"
#endif
#if COLLECT_DISK
				"k:K:"
#endif
#if COLLECT_LOAD
				"l:"
#endif
#if COLLECT_MEMORY
				"m:"
#endif /* COLLECT_MEMORY */
#if COLLECT_PING
				"p:P:"
#endif /* COLLECT_PING */
#if COLLECT_SENSORS
				"s:"
#endif
#if COLLECT_TRAFFIC
				"t:T:"
#endif
				"h");

		if (c == -1)
			break;

		switch (c)
		{
#if COLLECT_CPU
			case 'c':
				cpu_file = optarg;
				break;
#endif
			case 'd':
				if (change_basedir (optarg) != 0)
					exit (1);
				break;

#if COLLECT_DISK
			case 'k':
				disk_file = optarg;
				break;

			case 'K':
				partition_file = optarg;
				break;
#endif
#if COLLECT_LOAD
			case 'l':
				load_file = optarg;
				break;
#endif
#if COLLECT_MEMORY
			case 'm':
				mem_file = optarg;
				break;
#endif /* COLLECT_MEMORY */
#if COLLECT_PING
			case 'p':
				ping_file = optarg;
				break;

			case 'P':
				ping_host = optarg;
				break;
#endif /* COLLECT_PING */
#if COLLECT_SENSORS
			case 's':
				sensors_file = optarg;
				break;
#endif
#if COLLECT_TRAFFIC
			case 't':
				traffic_file = optarg;
				break;

			case 'T':
				traffic_device = optarg;
				break;
#endif
			case 'h':
			default:
				exit_usage (argv[0]);
		}
				
	}
