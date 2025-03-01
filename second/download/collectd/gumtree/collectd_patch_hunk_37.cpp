 
 	/* read options */
 	while (1)
 	{
 		int c;
 
-		c = getopt (argc, argv, "C:P:M:D:fh"
-#if HAVE_LIBRRD
-				"csl"
-#endif /* HAVE_LIBRRD */
-#if COLLECT_PING
-				"p:"
-#endif /* COLLECT_PING */
+		c = getopt (argc, argv, "hC:"
+#if COLLECT_DAEMON
+				"f"
+#endif
 		);
 
 		if (c == -1)
 			break;
 
 		switch (c)
 		{
-#ifdef HAVE_LIBRRD
-			case 'c':
-				operating_mode = MODE_CLIENT;
-				break;
-
-			case 's':
-				operating_mode = MODE_SERVER;
-				break;
-
-			case 'l':
-				operating_mode = MODE_LOCAL;
-				break;
-#endif /* HAVE_LIBRRD */
 			case 'C':
 				configfile = optarg;
 				break;
-			case 'P':
-				pidfile = optarg;
-				break;
-			case 'M':
-				plugindir = optarg;
-				break;
-			case 'D':
-				datadir = optarg;
-				break;
+#if COLLECT_DAEMON
 			case 'f':
 				daemonize = 0;
 				break;
-#if COLLECT_PING
-			case 'p':
-				if (num_pinghosts < MAX_PINGHOSTS)
-					pinghosts[num_pinghosts++] = optarg;
-				else
-					fprintf (stderr, "Maximum of %i ping hosts reached.\n", MAX_PINGHOSTS);
-				break;
-#endif /* COLLECT_PING */
+#endif /* COLLECT_DAEMON */
 			case 'h':
 			default:
 				exit_usage (argv[0]);
-		}
-				
-	}
+		} /* switch (c) */
+	} /* while (1) */
+
+#if COLLECT_DEBUG
+	if ((logfile = cf_get_option ("LogFile", LOGFILE)) != NULL)
+		DBG_STARTFILE (logfile, "Debug file opened.");
+#endif
 
 	/*
-	 * Load plugins and change to output directory
-	 * Loading plugins is done first so relative paths work as expected..
+	 * Read options from the config file, the environment and the command
+	 * line (in that order, with later options overwriting previous ones in
+	 * general).
+	 * Also, this will automatically load modules.
 	 */
-	if (plugin_load_all (plugindir) < 1)
+	if (cf_read (configfile))
 	{
-		fprintf (stderr, "Error: No plugins found.\n");
+		fprintf (stderr, "Error: Reading the config file failed!\n"
+				"Read the syslog for details.\n");
 		return (1);
 	}
 
+	/*
+	 * Change directory. We do this _after_ reading the config and loading
+	 * modules to relative paths work as expected.
+	 */
+	if ((datadir = cf_get_option ("DataDir", PKGLOCALSTATEDIR)) == NULL)
+	{
+		fprintf (stderr, "Don't have a datadir to use. This should not happen. Ever.");
+		return (1);
+	}
 	if (change_basedir (datadir))
 	{
 		fprintf (stderr, "Error: Unable to change to directory `%s'.\n", datadir);
 		return (1);
 	}
 
+#if COLLECT_DAEMON
 	/*
 	 * fork off child
 	 */
-#if COLLECT_DAEMON
 	sigChldAction.sa_handler = SIG_IGN;
 	sigaction (SIGCHLD, &sigChldAction, NULL);
 
+	if ((pidfile = cf_get_option ("PIDFile", PIDFILE)) == NULL)
+	{
+		fprintf (stderr, "Cannot obtain pidfile. This shoud not happen. Ever.");
+		return (1);
+	}
+
 	if (daemonize)
 	{
 		if ((pid = fork ()) == -1)
 		{
 			/* error */
 			fprintf (stderr, "fork: %s", strerror (errno));
