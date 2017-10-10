 		failed_errno = errno;
 		error("waitpid for %s failed: %s", argv0, strerror(errno));
 	} else if (waiting != pid) {
 		error("waitpid is confused (%s)", argv0);
 	} else if (WIFSIGNALED(status)) {
 		code = WTERMSIG(status);
-		if (code != SIGINT && code != SIGQUIT)
+		if (code != SIGINT && code != SIGQUIT && code != SIGPIPE)
 			error("%s died of signal %d", argv0, code);
 		/*
 		 * This return value is chosen so that code & 0xff
 		 * mimics the exit code that a POSIX shell would report for
 		 * a program that died from this signal.
 		 */
