 	return 0;
 } /* pidfile_remove */
 
 static int daemonize (void)
 {
 	struct rlimit rl;
+	int dev_null;
 
 	pid_t pid = 0;
 	int   i   = 0;
 
 	if (0 != chdir ("/")) {
 		fprintf (stderr, "Error: chdir() failed: %s\n", strerror (errno));
