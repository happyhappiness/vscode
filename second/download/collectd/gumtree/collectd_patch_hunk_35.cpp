 	{
 		fprintf (stderr, "Error: Unable to change to directory `%s'.\n", datadir);
 		return (1);
 	}
 
 	/*
-	 * install signal handlers
+	 * fork off child
 	 */
-	sigIntAction.sa_handler = sigIntHandler;
-	sigaction (SIGINT, &sigIntAction, NULL);
-
+#if COLLECT_DAEMON
 	sigChldAction.sa_handler = SIG_IGN;
 	sigaction (SIGCHLD, &sigChldAction, NULL);
 
-	/*
-	 * fork off child
-	 */
-#if COLLECT_DAEMON
 	if (daemonize)
 	{
 		if ((pid = fork ()) == -1)
 		{
 			/* error */
 			fprintf (stderr, "fork: %s", strerror (errno));
