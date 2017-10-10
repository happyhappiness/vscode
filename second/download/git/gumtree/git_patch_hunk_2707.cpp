 {
 	int flags = fcntl(fd, F_GETFD);
 	if (flags >= 0)
 		fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
 }
 
-static int wait_or_whine(pid_t pid, const char *argv0)
+static int wait_or_whine(pid_t pid, const char *argv0, int in_signal)
 {
 	int status, code = -1;
 	pid_t waiting;
 	int failed_errno = 0;
 
 	while ((waiting = waitpid(pid, &status, 0)) < 0 && errno == EINTR)
 		;	/* nothing */
+	if (in_signal)
+		return 0;
 
 	if (waiting < 0) {
 		failed_errno = errno;
 		error("waitpid for %s failed: %s", argv0, strerror(errno));
 	} else if (waiting != pid) {
 		error("waitpid is confused (%s)", argv0);
