 		}
 	} else {
 		if (!(module_chdir = normalize_path(module_dir, False, &module_dirlen)))
 			return path_failure(f_out, module_dir, False);
 		full_module_path = module_dir = module_chdir;
 	}
+	set_env_str("RSYNC_MODULE_PATH", full_module_path);
 
 	if (module_dirlen == 1) {
 		module_dirlen = 0;
 		set_filter_dir("/", 1);
 	} else
 		set_filter_dir(module_dir, module_dirlen);
 
 	p = lp_filter(i);
-	parse_rule(&daemon_filter_list, p, MATCHFLG_WORD_SPLIT,
+	parse_filter_str(&daemon_filter_list, p, rule_template(FILTRULE_WORD_SPLIT),
 		   XFLG_ABS_IF_SLASH | XFLG_DIR2WILD3);
 
 	p = lp_include_from(i);
-	parse_filter_file(&daemon_filter_list, p, MATCHFLG_INCLUDE,
+	parse_filter_file(&daemon_filter_list, p, rule_template(FILTRULE_INCLUDE),
 	    XFLG_ABS_IF_SLASH | XFLG_DIR2WILD3 | XFLG_OLD_PREFIXES | XFLG_FATAL_ERRORS);
 
 	p = lp_include(i);
-	parse_rule(&daemon_filter_list, p,
-		   MATCHFLG_INCLUDE | MATCHFLG_WORD_SPLIT,
+	parse_filter_str(&daemon_filter_list, p,
+		   rule_template(FILTRULE_INCLUDE | FILTRULE_WORD_SPLIT),
 		   XFLG_ABS_IF_SLASH | XFLG_DIR2WILD3 | XFLG_OLD_PREFIXES);
 
 	p = lp_exclude_from(i);
-	parse_filter_file(&daemon_filter_list, p, 0,
+	parse_filter_file(&daemon_filter_list, p, rule_template(0),
 	    XFLG_ABS_IF_SLASH | XFLG_DIR2WILD3 | XFLG_OLD_PREFIXES | XFLG_FATAL_ERRORS);
 
 	p = lp_exclude(i);
-	parse_rule(&daemon_filter_list, p, MATCHFLG_WORD_SPLIT,
+	parse_filter_str(&daemon_filter_list, p, rule_template(FILTRULE_WORD_SPLIT),
 		   XFLG_ABS_IF_SLASH | XFLG_DIR2WILD3 | XFLG_OLD_PREFIXES);
 
 	log_init(1);
 
 #ifdef HAVE_PUTENV
 	if (*lp_prexfer_exec(i) || *lp_postxfer_exec(i)) {
-		char *modname, *modpath, *hostaddr, *hostname, *username;
 		int status;
 
-		if (asprintf(&modname, "RSYNC_MODULE_NAME=%s", name) < 0
-		 || asprintf(&modpath, "RSYNC_MODULE_PATH=%s", full_module_path) < 0
-		 || asprintf(&hostaddr, "RSYNC_HOST_ADDR=%s", addr) < 0
-		 || asprintf(&hostname, "RSYNC_HOST_NAME=%s", host) < 0
-		 || asprintf(&username, "RSYNC_USER_NAME=%s", auth_user) < 0)
-			out_of_memory("rsync_module");
-		putenv(modname);
-		putenv(modpath);
-		putenv(hostaddr);
-		putenv(hostname);
-		putenv(username);
-		umask(orig_umask);
 		/* For post-xfer exec, fork a new process to run the rsync
 		 * daemon while this process waits for the exit status and
 		 * runs the indicated command at that point. */
 		if (*lp_postxfer_exec(i)) {
 			pid_t pid = fork();
 			if (pid < 0) {
 				rsyserr(FLOG, errno, "fork failed");
 				io_printf(f_out, "@ERROR: fork failed\n");
 				return -1;
 			}
 			if (pid) {
-				if (asprintf(&p, "RSYNC_PID=%ld", (long)pid) > 0)
-					putenv(p);
+				close(f_in);
+				if (f_out != f_in)
+					close(f_out);
+				set_env_num("RSYNC_PID", (long)pid);
 				if (wait_process(pid, &status, 0) < 0)
 					status = -1;
-				if (asprintf(&p, "RSYNC_RAW_STATUS=%d", status) > 0)
-					putenv(p);
+				set_env_num("RSYNC_RAW_STATUS", status);
 				if (WIFEXITED(status))
 					status = WEXITSTATUS(status);
 				else
 					status = -1;
-				if (asprintf(&p, "RSYNC_EXIT_STATUS=%d", status) > 0)
-					putenv(p);
+				set_env_num("RSYNC_EXIT_STATUS", status);
 				if (system(lp_postxfer_exec(i)) < 0)
 					status = -1;
 				_exit(status);
 			}
 		}
 		/* For pre-xfer exec, fork a child process to run the indicated
 		 * command, though it first waits for the parent process to
 		 * send us the user's request via a pipe. */
 		if (*lp_prexfer_exec(i)) {
-			int fds[2];
-			if (asprintf(&p, "RSYNC_PID=%ld", (long)getpid()) > 0)
-				putenv(p);
-			if (pipe(fds) < 0 || (pre_exec_pid = fork()) < 0) {
+			int arg_fds[2], error_fds[2];
+			set_env_num("RSYNC_PID", (long)getpid());
+			if (pipe(arg_fds) < 0 || pipe(error_fds) < 0 || (pre_exec_pid = fork()) < 0) {
 				rsyserr(FLOG, errno, "pre-xfer exec preparation failed");
 				io_printf(f_out, "@ERROR: pre-xfer exec preparation failed\n");
 				return -1;
 			}
 			if (pre_exec_pid == 0) {
 				char buf[BIGPATHBUFLEN];
 				int j, len;
-				close(fds[1]);
-				set_blocking(fds[0]);
-				len = read_arg_from_pipe(fds[0], buf, BIGPATHBUFLEN);
+				close(arg_fds[1]);
+				close(error_fds[0]);
+				pre_exec_arg_fd = arg_fds[0];
+				pre_exec_error_fd = error_fds[1];
+				set_blocking(pre_exec_arg_fd);
+				set_blocking(pre_exec_error_fd);
+				len = read_arg_from_pipe(pre_exec_arg_fd, buf, BIGPATHBUFLEN);
 				if (len <= 0)
 					_exit(1);
-				if (asprintf(&p, "RSYNC_REQUEST=%s", buf) > 0)
-					putenv(p);
+				set_env_str("RSYNC_REQUEST", buf);
 				for (j = 0; ; j++) {
-					len = read_arg_from_pipe(fds[0], buf,
+					len = read_arg_from_pipe(pre_exec_arg_fd, buf,
 								 BIGPATHBUFLEN);
 					if (len <= 0) {
 						if (!len)
 							break;
 						_exit(1);
 					}
-					if (asprintf(&p, "RSYNC_ARG%d=%s", j, buf) > 0)
+					if (asprintf(&p, "RSYNC_ARG%d=%s", j, buf) >= 0)
 						putenv(p);
 				}
-				close(fds[0]);
+				close(pre_exec_arg_fd);
 				close(STDIN_FILENO);
-				close(STDOUT_FILENO);
+				dup2(pre_exec_error_fd, STDOUT_FILENO);
+				close(pre_exec_error_fd);
 				status = system(lp_prexfer_exec(i));
 				if (!WIFEXITED(status))
 					_exit(1);
 				_exit(WEXITSTATUS(status));
 			}
-			close(fds[0]);
-			set_blocking(fds[1]);
-			pre_exec_fd = fds[1];
+			close(arg_fds[0]);
+			close(error_fds[1]);
+			pre_exec_arg_fd = arg_fds[1];
+			pre_exec_error_fd = error_fds[0];
+			set_blocking(pre_exec_arg_fd);
+			set_blocking(pre_exec_error_fd);
 		}
-		umask(0);
 	}
 #endif
 
 	if (use_chroot) {
 		/*
 		 * XXX: The 'use chroot' flag is a fairly reliable
