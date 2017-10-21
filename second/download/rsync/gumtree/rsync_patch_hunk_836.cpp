 			if (pid < 0) {
 				rsyserr(FLOG, errno, "fork failed");
 				io_printf(f_out, "@ERROR: fork failed\n");
 				return -1;
 			}
 			if (pid) {
-				char *ret1, *ret2;
+				if (asprintf(&p, "RSYNC_PID=%ld", (long)pid) > 0)
+					putenv(p);
 				if (wait_process(pid, &status, 0) < 0)
 					status = -1;
-				if (asprintf(&ret1, "RSYNC_RAW_STATUS=%d", status) > 0)
-					putenv(ret1);
+				if (asprintf(&p, "RSYNC_RAW_STATUS=%d", status) > 0)
+					putenv(p);
 				if (WIFEXITED(status))
 					status = WEXITSTATUS(status);
 				else
 					status = -1;
-				if (asprintf(&ret2, "RSYNC_EXIT_STATUS=%d", status) > 0)
-					putenv(ret2);
+				if (asprintf(&p, "RSYNC_EXIT_STATUS=%d", status) > 0)
+					putenv(p);
 				system(lp_postxfer_exec(i));
 				_exit(status);
 			}
 		}
 		/* For pre-xfer exec, fork a child process to run the indicated
 		 * command, though it first waits for the parent process to
 		 * send us the user's request via a pipe. */
 		if (*lp_prexfer_exec(i)) {
 			int fds[2];
+			if (asprintf(&p, "RSYNC_PID=%ld", (long)getpid()) > 0)
+				putenv(p);
 			if (pipe(fds) < 0 || (pre_exec_pid = fork()) < 0) {
 				rsyserr(FLOG, errno, "pre-xfer exec preparation failed");
 				io_printf(f_out, "@ERROR: pre-xfer exec preparation failed\n");
 				return -1;
 			}
 			if (pre_exec_pid == 0) {
