static void exit_usage (char *name)
{
	printf ("Usage: "PACKAGE" [OPTIONS]\n\n"
			
			"Available options:\n"
			"  General:\n"
			"    -C <file>       Configuration file.\n"
			"                    Default: "CONFIGFILE"\n"
			"    -P <file>       PID-file.\n"
			"                    Default: "PIDFILE"\n"
#if COLLECT_DAEMON
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
}