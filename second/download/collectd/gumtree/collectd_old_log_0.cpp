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