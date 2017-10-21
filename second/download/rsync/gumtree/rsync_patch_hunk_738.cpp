 		io_printf(f_out, "%s\n", sargs[i]);
 	}
 	io_printf(f_out, "\n");
 
 	if (protocol_version < 23) {
 		if (protocol_version == 22 || !am_sender)
-			io_start_multiplex_in(f_in);
+			io_start_multiplex_in();
 	}
 
 	return 0;
 }
 
 
 
 static int rsync_module(int f_in, int f_out, int i)
 {
-	int argc=0;
-	char *argv[MAX_ARGS];
+	int argc = 0;
+	int maxargs;
+	char **argv;
 	char **argp;
 	char line[MAXPATHLEN];
 	uid_t uid = (uid_t)-2;  /* canonically "nobody" */
 	gid_t gid = (gid_t)-2;
 	char *p;
 	char *addr = client_addr(f_in);
 	char *host = client_name(f_in);
 	char *name = lp_name(i);
 	int use_chroot = lp_use_chroot(i);
-	int start_glob=0;
+	int start_glob = 0;
 	int ret;
-	char *request=NULL;
+	char *request = NULL;
 
 	if (!allow_access(addr, host, lp_hosts_allow(i), lp_hosts_deny(i))) {
-		rprintf(FERROR,"rsync denied on module %s from %s (%s)\n",
+		rprintf(FLOG, "rsync denied on module %s from %s (%s)\n",
 			name, host, addr);
-		io_printf(f_out, "@ERROR: access denied to %s from %s (%s)\n",
-			  name, host, addr);
+		if (!lp_list(i))
+			io_printf(f_out, "@ERROR: Unknown module '%s'\n", name);
+		else {
+			io_printf(f_out,
+				  "@ERROR: access denied to %s from %s (%s)\n",
+				  name, host, addr);
+		}
 		return -1;
 	}
 
 	if (am_daemon && am_server) {
-		rprintf(FINFO, "rsync allowed access on module %s from %s (%s)\n",
+		rprintf(FLOG, "rsync allowed access on module %s from %s (%s)\n",
 			name, host, addr);
 	}
 
 	if (!claim_connection(lp_lock_file(i), lp_max_connections(i))) {
 		if (errno) {
-			rprintf(FERROR,"failed to open lock file %s : %s\n",
-				lp_lock_file(i), strerror(errno));
-			io_printf(f_out, "@ERROR: failed to open lock file %s : %s\n",
-				  lp_lock_file(i), strerror(errno));
+			rsyserr(FLOG, errno, "failed to open lock file %s",
+				lp_lock_file(i));
+			io_printf(f_out, "@ERROR: failed to open lock file %s\n",
+				  lp_lock_file(i));
 		} else {
-			rprintf(FERROR,"max connections (%d) reached\n",
+			rprintf(FLOG, "max connections (%d) reached\n",
 				lp_max_connections(i));
 			io_printf(f_out, "@ERROR: max connections (%d) reached - try again later\n",
 				lp_max_connections(i));
 		}
 		return -1;
 	}
