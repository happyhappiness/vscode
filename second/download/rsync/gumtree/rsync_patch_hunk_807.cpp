 		set_filter_dir("/", 1);
 	} else
 		set_filter_dir(lp_path(i), module_dirlen);
 
 	p = lp_filter(i);
 	parse_rule(&server_filter_list, p, MATCHFLG_WORD_SPLIT,
-		   XFLG_ANCHORED2ABS);
+		   XFLG_ABS_IF_SLASH);
 
 	p = lp_include_from(i);
 	parse_filter_file(&server_filter_list, p, MATCHFLG_INCLUDE,
-	    XFLG_ANCHORED2ABS | XFLG_OLD_PREFIXES | XFLG_FATAL_ERRORS);
+	    XFLG_ABS_IF_SLASH | XFLG_OLD_PREFIXES | XFLG_FATAL_ERRORS);
 
 	p = lp_include(i);
 	parse_rule(&server_filter_list, p,
 		   MATCHFLG_INCLUDE | MATCHFLG_WORD_SPLIT,
-		   XFLG_ANCHORED2ABS | XFLG_OLD_PREFIXES);
+		   XFLG_ABS_IF_SLASH | XFLG_OLD_PREFIXES);
 
 	p = lp_exclude_from(i);
 	parse_filter_file(&server_filter_list, p, 0,
-	    XFLG_ANCHORED2ABS | XFLG_OLD_PREFIXES | XFLG_FATAL_ERRORS);
+	    XFLG_ABS_IF_SLASH | XFLG_OLD_PREFIXES | XFLG_FATAL_ERRORS);
 
 	p = lp_exclude(i);
 	parse_rule(&server_filter_list, p, MATCHFLG_WORD_SPLIT,
-		   XFLG_ANCHORED2ABS | XFLG_OLD_PREFIXES);
+		   XFLG_ABS_IF_SLASH | XFLG_OLD_PREFIXES);
 
 	log_init();
 
+#ifdef HAVE_PUTENV
+	if (*lp_prexfer_exec(i) || *lp_postxfer_exec(i)) {
+		char *modname, *modpath, *hostaddr, *hostname, *username;
+		int status;
+		if (asprintf(&modname, "RSYNC_MODULE_NAME=%s", name) < 0
+		 || asprintf(&modpath, "RSYNC_MODULE_PATH=%s", lp_path(i)) < 0
+		 || asprintf(&hostaddr, "RSYNC_HOST_ADDR=%s", addr) < 0
+		 || asprintf(&hostname, "RSYNC_HOST_NAME=%s", host) < 0
+		 || asprintf(&username, "RSYNC_USER_NAME=%s", auth_user) < 0)
+			out_of_memory("rsync_module");
+		putenv(modname);
+		putenv(modpath);
+		putenv(hostaddr);
+		putenv(hostname);
+		putenv(username);
+		umask(orig_umask);
+		/* For post-xfer exec, fork a new process to run the rsync
+		 * daemon while this process waits for the exit status and
+		 * runs the indicated command at that point. */
+		if (*lp_postxfer_exec(i)) {
+			pid_t pid = fork();
+			if (pid < 0) {
+				rsyserr(FLOG, errno, "fork failed");
+				io_printf(f_out, "@ERROR: fork failed\n");
+				return -1;
+			}
+			if (pid) {
+				char *ret1, *ret2;
+				if (wait_process(pid, &status, 0) < 0)
+					status = -1;
+				if (asprintf(&ret1, "RSYNC_RAW_STATUS=%d", status) > 0)
+					putenv(ret1);
+				if (WIFEXITED(status))
+					status = WEXITSTATUS(status);
+				else
+					status = -1;
+				if (asprintf(&ret2, "RSYNC_EXIT_STATUS=%d", status) > 0)
+					putenv(ret2);
+				system(lp_postxfer_exec(i));
+				_exit(status);
+			}
+		}
+		/* For pre-xfer exec, fork a child process to run the indicated
+		 * command, though it first waits for the parent process to
+		 * send us the user's request via a pipe. */
+		if (*lp_prexfer_exec(i)) {
+			int fds[2];
+			if (pipe(fds) < 0 || (pre_exec_pid = fork()) < 0) {
+				rsyserr(FLOG, errno, "pre-xfer exec preparation failed");
+				io_printf(f_out, "@ERROR: pre-xfer exec preparation failed\n");
+				return -1;
+			}
+			if (pre_exec_pid == 0) {
+				char buf[BIGPATHBUFLEN];
+				int j, len;
+				close(fds[1]);
+				set_blocking(fds[0]);
+				len = read_arg_from_pipe(fds[0], buf, BIGPATHBUFLEN);
+				if (len <= 0)
+					_exit(1);
+				if (asprintf(&p, "RSYNC_REQUEST=%s", buf) < 0)
+					out_of_memory("rsync_module");
+				putenv(p);
+				for (j = 0; ; j++) {
+					len = read_arg_from_pipe(fds[0], buf,
+								 BIGPATHBUFLEN);
+					if (len <= 0) {
+						if (!len)
+							break;
+						_exit(1);
+					}
+					if (asprintf(&p, "RSYNC_ARG%d=%s", j, buf) < 0)
+						out_of_memory("rsync_module");
+					putenv(p);
+				}
+				close(fds[0]);
+				close(STDIN_FILENO);
+				close(STDOUT_FILENO);
+				status = system(lp_prexfer_exec(i));
+				if (!WIFEXITED(status))
+					_exit(1);
+				_exit(WEXITSTATUS(status));
+			}
+			close(fds[0]);
+			set_blocking(fds[1]);
+			pre_exec_fd = fds[1];
+		}
+		umask(0);
+	}
+#endif
+
 	if (use_chroot) {
 		/*
 		 * XXX: The 'use chroot' flag is a fairly reliable
 		 * source of confusion, because it fails under two
 		 * important circumstances: running as non-root,
 		 * running on Win32 (or possibly others).  On the
