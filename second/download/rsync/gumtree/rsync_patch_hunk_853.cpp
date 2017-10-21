 				     default_af_hint);
 	if (fd == -1)
 		exit_cleanup(RERR_SOCKETIO);
 
 	set_socket_options(fd, sockopts);
 
-	ret = start_inband_exchange(user, path, fd, fd, argc);
+#ifdef ICONV_CONST
+	setup_iconv();
+#endif
+
+	ret = start_inband_exchange(fd, fd, user, remote_argc, remote_argv);
 
 	return ret ? ret : client_run(fd, fd, -1, argc, argv);
 }
 
-int start_inband_exchange(char *user, char *path, int f_in, int f_out,
-			  int argc)
+static int exchange_protocols(int f_in, int f_out, char *buf, size_t bufsiz, int am_client)
 {
-	int i;
+	int remote_sub = -1;
+#if SUBPROTOCOL_VERSION != 0
+	int our_sub = protocol_version < PROTOCOL_VERSION ? 0 : SUBPROTOCOL_VERSION;
+#else
+	int our_sub = 0;
+#endif
+	char *motd;
+
+	io_printf(f_out, "@RSYNCD: %d.%d\n", protocol_version, our_sub);
+
+	if (!am_client) {
+		motd = lp_motd_file();
+		if (motd && *motd) {
+			FILE *f = fopen(motd,"r");
+			while (f && !feof(f)) {
+				int len = fread(buf, 1, bufsiz - 1, f);
+				if (len > 0)
+					write_buf(f_out, buf, len);
+			}
+			if (f)
+				fclose(f);
+			write_sbuf(f_out, "\n");
+		}
+	}
+
+	/* This strips the \n. */
+	if (!read_line_old(f_in, buf, bufsiz)) {
+		if (am_client)
+			rprintf(FERROR, "rsync: did not see server greeting\n");
+		return -1;
+	}
+
+	if (sscanf(buf, "@RSYNCD: %d.%d", &remote_protocol, &remote_sub) < 1) {
+		if (am_client)
+			rprintf(FERROR, "rsync: server sent \"%s\" rather than greeting\n", buf);
+		else
+			io_printf(f_out, "@ERROR: protocol startup error\n");
+		return -1;
+	}
+
+	if (remote_sub < 0) {
+		if (remote_protocol == 30) {
+			if (am_client)
+				rprintf(FERROR, "rsync: server is speaking an incompatible beta of protocol 30\n");
+			else
+				io_printf(f_out, "@ERROR: your client is speaking an incompatible beta of protocol 30\n");
+			return -1;
+		}
+		remote_sub = 0;
+	}
+
+	if (protocol_version > remote_protocol) {
+		protocol_version = remote_protocol;
+		if (remote_sub)
+			protocol_version--;
+	} else if (protocol_version == remote_protocol) {
+		if (remote_sub != our_sub)
+			protocol_version--;
+	}
+#if SUBPROTOCOL_VERSION != 0
+	else if (protocol_version < remote_protocol) {
+		if (our_sub)
+			protocol_version--;
+	}
+#endif
+
+	if (protocol_version >= 30)
+		rl_nulls = 1;
+
+	return 0;
+}
+
+int start_inband_exchange(int f_in, int f_out, const char *user, int argc, char *argv[])
+{
+	int i, modlen;
+	char line[BIGPATHBUFLEN];
 	char *sargs[MAX_ARGS];
 	int sargc = 0;
-	char line[BIGPATHBUFLEN];
-	char *p;
+	char *p, *modname;
 
-	if (argc == 0 && !am_sender)
-		list_only |= 1;
+	assert(argc > 0);
 
-	if (*path == '/') {
+	if (**argv == '/') {
 		rprintf(FERROR,
 			"ERROR: The remote path must start with a module name\n");
 		return -1;
 	}
 
+	if (!(p = strchr(*argv, '/')))
+		modlen = strlen(*argv);
+	else
+		modlen = p - *argv;
+
+	if (!(modname = new_array(char, modlen+1+1))) /* room for '/' & '\0' */
+		out_of_memory("start_inband_exchange");
+	strlcpy(modname, *argv, modlen + 1);
+	modname[modlen] = '/';
+	modname[modlen+1] = '\0';
+
 	if (!user)
 		user = getenv("USER");
 	if (!user)
 		user = getenv("LOGNAME");
 
-	io_printf(f_out, "@RSYNCD: %d\n", protocol_version);
-
-	if (!read_line(f_in, line, sizeof line - 1)) {
-		rprintf(FERROR, "rsync: did not see server greeting\n");
+	if (exchange_protocols(f_in, f_out, line, sizeof line, 1) < 0)
 		return -1;
-	}
-
-	if (sscanf(line,"@RSYNCD: %d", &remote_protocol) != 1) {
-		/* note that read_line strips of \n or \r */
-		rprintf(FERROR, "rsync: server sent \"%s\" rather than greeting\n",
-			line);
-		return -1;
-	}
-	if (protocol_version > remote_protocol)
-		protocol_version = remote_protocol;
-
-	if (list_only && protocol_version >= 29)
-		list_only |= 2;
 
 	/* set daemon_over_rsh to false since we need to build the
 	 * true set of args passed through the rsh/ssh connection;
 	 * this is a no-op for direct-socket-connection mode */
 	daemon_over_rsh = 0;
 	server_options(sargs, &sargc);
 
+	if (sargc >= MAX_ARGS - 2)
+		goto arg_overflow;
+
 	sargs[sargc++] = ".";
 
-	if (path && *path)
-		sargs[sargc++] = path;
+	while (argc > 0) {
+		if (sargc >= MAX_ARGS - 1) {
+		  arg_overflow:
+			rprintf(FERROR, "internal: args[] overflowed in do_cmd()\n");
+			exit_cleanup(RERR_SYNTAX);
+		}
+		if (strncmp(*argv, modname, modlen) == 0
+		 && argv[0][modlen] == '\0')
+			sargs[sargc++] = modname; /* we send "modname/" */
+		else
+			sargs[sargc++] = *argv;
+		argv++;
+		argc--;
+	}
 
 	sargs[sargc] = NULL;
 
 	if (verbose > 1)
-		print_child_argv(sargs);
+		print_child_argv("sending daemon args:", sargs);
 
-	p = strchr(path,'/');
-	if (p) *p = 0;
-	io_printf(f_out, "%s\n", path);
-	if (p) *p = '/';
+	io_printf(f_out, "%.*s\n", modlen, modname);
 
 	/* Old servers may just drop the connection here,
 	 rather than sending a proper EXIT command.  Yuck. */
 	kluge_around_eof = list_only && protocol_version < 25 ? 1 : 0;
 
 	while (1) {
-		if (!read_line(f_in, line, sizeof line - 1)) {
+		if (!read_line_old(f_in, line, sizeof line)) {
 			rprintf(FERROR, "rsync: didn't get server startup line\n");
 			return -1;
 		}
 
 		if (strncmp(line,"@RSYNCD: AUTHREQD ",18) == 0) {
 			auth_client(f_out, user, line+18);
