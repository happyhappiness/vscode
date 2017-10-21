 
 	log_open();
 
 	rprintf(FINFO,"rsyncd version %s starting\n",VERSION);
 
 	if (((pid_file = lp_pid_file()) != NULL) && (*pid_file != '\0')) {
-		FILE *f;
+		char pidbuf[16];
+		int fd;
 		int pid = (int) getpid();
 		cleanup_set_pid(pid);
-		if ((f = fopen(lp_pid_file(), "w")) == NULL) {
+		if ((fd = do_open(lp_pid_file(), O_WRONLY|O_CREAT|O_TRUNC,
+					0666 & ~orig_umask)) == -1) {
 		    cleanup_set_pid(0);
 		    fprintf(stderr,"failed to create pid file %s\n", pid_file);
 		    exit_cleanup(RERR_FILEIO);
 		}
-		fprintf(f, "%d\n", pid);
-		fclose(f);
+		slprintf(pidbuf, sizeof(pidbuf), "%d\n", pid);
+		write(fd, pidbuf, strlen(pidbuf));
+		close(fd);
 	}
 
 	start_accept_loop(rsync_port, start_daemon);
 	return -1;
 }
 
