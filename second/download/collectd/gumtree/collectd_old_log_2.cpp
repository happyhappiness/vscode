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
			"  Swap:      %s\n"
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
			(COLLECT_SWAP    ? "yes" : "no"),
			(COLLECT_TRAFFIC ? "yes" : "no"),
			PACKAGE, VERSION);