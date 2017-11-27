printf ("Usage: %s [OPTIONS]\n\n"
			
			"Available options:\n"
			"  General:\n"
			"    -c              Start in client (sender) mode\n"
			"    -d <dir>        Base directory to use. Default: /var/lib/collectd\n"
			"    -l              Start in local mode (no network)\n"
			"    -P <dir>        Set the plugin-directory\n"
			"    -s              Start in server (listener) mode\n"
#if COLLECT_PING
			"  Ping:\n"
			"    -p <host>       Host to ping periodically, may be repeated to ping\n"
			"                    more than one host.\n"
#endif /* COLLECT_PING */
			"\n%s %s, http://verplant.org/collectd/\n"
			"by Florian octo Forster <octo@verplant.org>\n"
			"hddtemp support by Vincent Stehl� <vincent.stehle@free.fr>\n",
			PACKAGE, PACKAGE, VERSION);