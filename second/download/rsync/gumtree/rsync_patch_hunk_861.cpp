 #endif
 	SIGACTION(SIGCHLD, remember_children);
 
 	return rsync_module(f_in, f_out, i, addr, host);
 }
 
+static void create_pid_file(void)
+{
+	char *pid_file = lp_pid_file();
+	char pidbuf[16];
+	pid_t pid = getpid();
+	int fd;
+
+	if (!pid_file || !*pid_file)
+		return;
+
+	cleanup_set_pid(pid);
+	if ((fd = do_open(pid_file, O_WRONLY|O_CREAT|O_EXCL, 0666 & ~orig_umask)) == -1) {
+		cleanup_set_pid(0);
+		fprintf(stderr, "failed to create pid file %s: %s\n", pid_file, strerror(errno));
+		rsyserr(FLOG, errno, "failed to create pid file %s", pid_file);
+		exit_cleanup(RERR_FILEIO);
+	}
+	snprintf(pidbuf, sizeof pidbuf, "%ld\n", (long)pid);
+	write(fd, pidbuf, strlen(pidbuf));
+	close(fd);
+}
+
+/* Become a daemon, discarding the controlling terminal. */
+static void become_daemon(void)
+{
+	int i;
+	pid_t pid = fork();
+
+	if (pid) {
+		if (pid < 0) {
+			fprintf(stderr, "failed to fork: %s\n", strerror(errno));
+			exit_cleanup(RERR_FILEIO);
+		}
+		_exit(0);
+	}
+
+	create_pid_file();
+
+	/* detach from the terminal */
+#ifdef HAVE_SETSID
+	setsid();
+#elif defined TIOCNOTTY
+	i = open("/dev/tty", O_RDWR);
+	if (i >= 0) {
+		ioctl(i, (int)TIOCNOTTY, (char *)0);
+		close(i);
+	}
+#endif
+	/* make sure that stdin, stdout an stderr don't stuff things
+	 * up (library functions, for example) */
+	for (i = 0; i < 3; i++) {
+		close(i);
+		open("/dev/null", O_RDWR);
+	}
+}
+
 int daemon_main(void)
 {
-	char *pid_file;
+	if (!config_file) {
+		if (am_server && am_root <= 0)
+			config_file = RSYNCD_USERCONF;
+		else
+			config_file = RSYNCD_SYSCONF;
+	}
 
 	if (is_a_socket(STDIN_FILENO)) {
 		int i;
 
 		/* we are running via inetd - close off stdout and
 		 * stderr so that library functions (and getopt) don't
