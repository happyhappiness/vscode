 void exit_usage (char *name)
 {
 	printf ("Usage: %s [OPTIONS]\n\n"
 			
 			"Available options:\n"
 			"  General:\n"
-			"    -c              Start in client (sender) mode\n"
 			"    -d <dir>        Base directory to use. Default: /var/lib/collectd\n"
-			"    -l              Start in local mode (no network)\n"
 			"    -P <dir>        Set the plugin-directory\n"
+			"    -f              Don't fork to the background\n"
+#ifdef HAVE_LIBRRD
+			"    -l              Start in local mode (no network)\n"
+			"    -c              Start in client (sender) mode\n"
 			"    -s              Start in server (listener) mode\n"
+#endif /* HAVE_LIBRRD */
 #if COLLECT_PING
 			"  Ping:\n"
 			"    -p <host>       Host to ping periodically, may be repeated to ping\n"
 			"                    more than one host.\n"
 #endif /* COLLECT_PING */
 			"\n%s %s, http://verplant.org/collectd/\n"
 			"by Florian octo Forster <octo@verplant.org>\n"
-			"hddtemp support by Vincent Stehlé <vincent.stehle@free.fr>\n",
+			"for contributions see `AUTHORS'\n",
 			PACKAGE, PACKAGE, VERSION);
 	exit (0);
 }
 
 int start_client (void)
 {
