 
 	if (protect_args)
 		send_protected_args(f_out, sargs);
 
 	if (protocol_version < 23) {
 		if (protocol_version == 22 || !am_sender)
-			io_start_multiplex_in();
+			io_start_multiplex_in(f_in);
 	}
 
 	free(modname);
 
 	return 0;
 }
 
-static char *finish_pre_exec(pid_t pid, int fd, char *request,
+static char *finish_pre_exec(pid_t pid, int write_fd, int read_fd, char *request,
 			     char **early_argv, char **argv)
 {
-	int j = 0, status = -1;
+	char buf[BIGPATHBUFLEN], *bp;
+	int j = 0, status = -1, msglen = sizeof buf - 1;
 
 	if (!request)
 		request = "(NONE)";
 
-	write_buf(fd, request, strlen(request)+1);
+	write_buf(write_fd, request, strlen(request)+1);
 	if (early_argv) {
 		for ( ; *early_argv; early_argv++)
-			write_buf(fd, *early_argv, strlen(*early_argv)+1);
+			write_buf(write_fd, *early_argv, strlen(*early_argv)+1);
 		j = 1; /* Skip arg0 name in argv. */
 	}
-	for ( ; argv[j]; j++) {
-		write_buf(fd, argv[j], strlen(argv[j])+1);
-		if (argv[j][0] == '.' && argv[j][1] == '\0')
-			break;
+	for ( ; argv[j]; j++)
+		write_buf(write_fd, argv[j], strlen(argv[j])+1);
+	write_byte(write_fd, 0);
+
+	close(write_fd);
+
+	/* Read the stdout from the pre-xfer exec program.  This it is only
+	 * displayed to the user if the script also returns an error status. */
+	for (bp = buf; msglen > 0; msglen -= j) {
+		if ((j = read(read_fd, bp, msglen)) <= 0) {
+			if (j == 0)
+				break;
+			if (errno == EINTR)
+				continue;
+			break; /* Just ignore the read error for now... */
+		}
+		bp += j;
+		if (j > 1 && bp[-1] == '\n' && bp[-2] == '\r') {
+			bp--;
+			j--;
+			bp[-1] = '\n';
+		}
 	}
-	write_byte(fd, 0);
+	*bp = '\0';
 
-	close(fd);
+	close(read_fd);
 
 	if (wait_process(pid, &status, 0) < 0
 	 || !WIFEXITED(status) || WEXITSTATUS(status) != 0) {
 		char *e;
-		if (asprintf(&e, "pre-xfer exec returned failure (%d)%s%s\n",
+		if (asprintf(&e, "pre-xfer exec returned failure (%d)%s%s%s\n%s",
 			     status, status < 0 ? ": " : "",
-			     status < 0 ? strerror(errno) : "") < 0)
-			out_of_memory("finish_pre_exec");
+			     status < 0 ? strerror(errno) : "",
+			     *buf ? ":" : "", buf) < 0)
+			return "out_of_memory in finish_pre_exec\n";
 		return e;
 	}
 	return NULL;
 }
 
+#ifdef HAVE_PUTENV
 static int read_arg_from_pipe(int fd, char *buf, int limit)
 {
 	char *bp = buf, *eob = buf + limit - 1;
 
 	while (1) {
-	    int got = read(fd, bp, 1);
-	    if (got != 1) {
-		if (got < 0 && errno == EINTR)
-			continue;
-		return -1;
-	    }
-	    if (*bp == '\0')
-		break;
-	    if (bp < eob)
-		bp++;
+		int got = read(fd, bp, 1);
+		if (got != 1) {
+			if (got < 0 && errno == EINTR)
+				continue;
+			return -1;
+		}
+		if (*bp == '\0')
+			break;
+		if (bp < eob)
+			bp++;
 	}
 	*bp = '\0';
 
 	return bp - buf;
 }
+#endif
 
 static int path_failure(int f_out, const char *dir, BOOL was_chdir)
 {
 	if (was_chdir)
 		rsyserr(FLOG, errno, "chdir %s failed\n", dir);
 	else
 		rprintf(FLOG, "normalize_path(%s) failed\n", dir);
 	io_printf(f_out, "@ERROR: chdir failed\n");
 	return -1;
 }
 
-static int rsync_module(int f_in, int f_out, int i, char *addr, char *host)
+static int add_a_group(int f_out, const char *gname)
+{
+	gid_t gid;
+	if (!group_to_gid(gname, &gid, True)) {
+		rprintf(FLOG, "Invalid gid %s\n", gname);
+		io_printf(f_out, "@ERROR: invalid gid %s\n", gname);
+		return -1;
+	}
+	if (gid_count == MAX_GID_LIST) {
+		rprintf(FLOG, "Too many groups specified via gid parameter.\n");
+		io_printf(f_out, "@ERROR: too many groups\n");
+		return -1;
+	}
+	gid_list[gid_count++] = gid;
+	return 0;
+}
+
+#ifdef HAVE_GETGROUPLIST
+static int want_all_groups(int f_out, uid_t uid)
+{
+	const char *err;
+	gid_count = MAX_GID_LIST;
+	if ((err = getallgroups(uid, gid_list, &gid_count)) != NULL) {
+		rsyserr(FLOG, errno, "%s", err);
+		io_printf(f_out, "@ERROR: %s\n", err);
+		return -1;
+	}
+	return 0;
+}
+#elif defined HAVE_INITGROUPS
+static struct passwd *want_all_groups(int f_out, uid_t uid)
+{
+	struct passwd *pw;
+	if ((pw = getpwuid(uid)) == NULL) {
+		rsyserr(FLOG, errno, "getpwuid failed");
+		io_printf(f_out, "@ERROR: getpwuid failed\n");
+		return NULL;
+	}
+	/* Start with the default group and initgroups() will add the reset. */
+	gid_count = 1;
+	gid_list[0] = pw->pw_gid;
+	return pw;
+}
+#endif
+
+static void set_env_str(const char *var, const char *str)
+{
+#ifdef HAVE_PUTENV
+	char *mem;
+	if (asprintf(&mem, "%s=%s", var, str) < 0)
+		out_of_memory("set_env_str");
+	putenv(mem);
+#endif
+}
+
+#ifdef HAVE_PUTENV
+static void set_env_num(const char *var, long num)
+{
+	char *mem;
+	if (asprintf(&mem, "%s=%ld", var, num) < 0)
+		out_of_memory("set_env_num");
+	putenv(mem);
+}
+#endif
+
+static int rsync_module(int f_in, int f_out, int i, const char *addr, const char *host)
 {
 	int argc;
 	char **argv, **orig_argv, **orig_early_argv, *module_chdir;
 	char line[BIGPATHBUFLEN];
-	uid_t uid = (uid_t)-2;  /* canonically "nobody" */
-	gid_t gid = (gid_t)-2;
+#if defined HAVE_INITGROUPS && !defined HAVE_GETGROUPLIST
+	struct passwd *pw = NULL;
+#endif
+	uid_t uid;
+	int set_uid;
 	char *p, *err_msg = NULL;
 	char *name = lp_name(i);
 	int use_chroot = lp_use_chroot(i);
-	int ret, pre_exec_fd = -1;
+	int ret, pre_exec_arg_fd = -1, pre_exec_error_fd = -1;
+	int save_munge_symlinks;
 	pid_t pre_exec_pid = 0;
 	char *request = NULL;
 
+	set_env_str("RSYNC_MODULE_NAME", name);
+
 #ifdef ICONV_OPTION
 	iconv_opt = lp_charset(i);
 	if (*iconv_opt)
 		setup_iconv();
 	iconv_opt = NULL;
 #endif
 
-	if (!allow_access(addr, host, lp_hosts_allow(i), lp_hosts_deny(i))) {
+	/* If reverse lookup is disabled globally but enabled for this module,
+	 * we need to do it now before the access check. */
+	if (host == undetermined_hostname && lp_reverse_lookup(i))
+		host = client_name(f_in);
+	set_env_str("RSYNC_HOST_NAME", host);
+	set_env_str("RSYNC_HOST_ADDR", addr);
+
+	if (!allow_access(addr, &host, i)) {
 		rprintf(FLOG, "rsync denied on module %s from %s (%s)\n",
 			name, host, addr);
 		if (!lp_list(i))
 			io_printf(f_out, "@ERROR: Unknown module '%s'\n", name);
 		else {
 			io_printf(f_out,
