 		else if (kid < 0)
 			syslog (LOG_ERR, "kstat chain update failed");
 		/* else: everything works as expected */
 	}
 
 	return;
-}
+} /* static void update_kstat (void) */
 #endif /* HAVE_LIBKSTAT */
 
-void exit_usage (char *name)
+/* TODO
+ * Remove all settings but `-f' and `-C'
+ */
+static void exit_usage (char *name)
 {
-	printf ("Usage: %s [OPTIONS]\n\n"
+	printf ("Usage: "PACKAGE" [OPTIONS]\n\n"
 			
 			"Available options:\n"
 			"  General:\n"
-			/*
-			"    -C <dir>        Configuration file.\n"
-			"                    Default: %s\n"
-			*/
-			"    -P <file>       PID File.\n"
-			"                    Default: %s\n"
-			"    -M <dir>        Module/Plugin directory.\n"
-			"                    Default: %s\n"
-			"    -D <dir>        Data storage directory.\n"
-			"                    Default: %s\n"
+			"    -C <file>       Configuration file.\n"
+			"                    Default: "CONFIGFILE"\n"
+#if COLLECT_DAEMON
 			"    -f              Don't fork to the background.\n"
-#ifdef HAVE_LIBRRD
-			"    -l              Start in local mode (no network).\n"
-			"    -c              Start in client (sender) mode.\n"
-			"    -s              Start in server (listener) mode.\n"
-#endif /* HAVE_LIBRRD */
-#if COLLECT_PING
-			"  Ping:\n"
-			"    -p <host>       Host to ping periodically, may be repeated to ping\n"
-			"                    more than one host.\n"
-#endif /* COLLECT_PING */
-			"\n%s %s, http://verplant.org/collectd/\n"
+#endif
+			"\nBuiltin defaults:\n"
+			"  Config-File       "CONFIGFILE"\n"
+			"  PID-File          "PIDFILE"\n"
+			"  Data-Directory    "PKGLOCALSTATEDIR"\n"
+#if COLLECT_DEBUG
+			"  Log-File          "LOGFILE"\n"
+#endif
+			"\n"PACKAGE" "VERSION", http://verplant.org/collectd/\n"
 			"by Florian octo Forster <octo@verplant.org>\n"
-			"for contributions see `AUTHORS'\n",
-			PACKAGE, /* CONFIGFILE, */ PIDFILE, PLUGINDIR, PKGLOCALSTATEDIR, PACKAGE, VERSION);
+			"for contributions see `AUTHORS'\n");
 	exit (0);
-}
+} /* static void exit_usage (char *name) */
 
-int start_client (void)
+static int start_client (void)
 {
 	int sleepingtime;
 
-#ifdef HAVE_LIBKSTAT
+#if HAVE_LIBKSTAT
 	kc = NULL;
 	update_kstat ();
 #endif
 
-#ifdef HAVE_LIBSTATGRAB
+#if HAVE_LIBSTATGRAB
 	if (sg_init ())
 	{
 		syslog (LOG_ERR, "sg_init: %s", sg_str_error (sg_get_error ()));
 		return (-1);
 	}
 
