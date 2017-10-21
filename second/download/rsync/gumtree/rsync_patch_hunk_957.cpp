 		argv++;
 		argc--;
 	}
 
 	sargs[sargc] = NULL;
 
-	if (verbose > 1)
+	if (DEBUG_GTE(CMD, 1))
 		print_child_argv("sending daemon args:", sargs);
 
 	io_printf(f_out, "%.*s\n", modlen, modname);
 
 	/* Old servers may just drop the connection here,
 	 rather than sending a proper EXIT command.  Yuck. */
 	kluge_around_eof = list_only && protocol_version < 25 ? 1 : 0;
 
 	while (1) {
-		if (!read_line_old(f_in, line, sizeof line)) {
+		if (!read_line_old(f_in, line, sizeof line, 0)) {
 			rprintf(FERROR, "rsync: didn't get server startup line\n");
 			return -1;
 		}
 
 		if (strncmp(line,"@RSYNCD: AUTHREQD ",18) == 0) {
 			auth_client(f_out, user, line+18);
