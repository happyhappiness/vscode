void exit_usage (char *name)
{
	printf ("Usage: %s [OPTIONS]\n\n"
			
			"Available options:\n"
			"  General:\n"
			/*
			"    -C <dir>        Configuration file.\n"
			"                    Default: %s\n"
			*/
			"    -P <file>       PID File.\n"
			"                    Default: %s\n"
			"    -M <dir>        Module/Plugin directory.\n"
			"                    Default: %s\n"
			"    -D <dir>        Data storage directory.\n"
			"                    Default: %s\n"
			"    -f              Don't fork to the background.\n"
#ifdef HAVE_LIBRRD
			"    -l              Start in local mode (no network).\n"
			"    -c              Start in client (sender) mode.\n"
			"    -s              Start in server (listener) mode.\n"
#endif /* HAVE_LIBRRD */
#if COLLECT_PING
			"  Ping:\n"
			"    -p <host>       Host to ping periodically, may be repeated to ping\n"
			"                    more than one host.\n"
#endif /* COLLECT_PING */
			"\n%s %s, http://verplant.org/collectd/\n"
			"by Florian octo Forster <octo@verplant.org>\n"
			"for contributions see `AUTHORS'\n",
			PACKAGE, /* CONFIGFILE, */ PIDFILE, PLUGINDIR, PKGLOCALSTATEDIR, PACKAGE, VERSION);
	exit (0);
}

int start_client (void)
{
	int sleepingtime;
