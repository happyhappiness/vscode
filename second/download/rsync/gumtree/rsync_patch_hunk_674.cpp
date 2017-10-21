 /* send a list of available modules to the client. Don't list those
    with "list = False". */
 static void send_listing(int fd)
 {
 	int n = lp_numservices();
 	int i;
-	extern int remote_version;
 
 	for (i=0;i<n;i++)
 		if (lp_list(i))
-		    io_printf(fd, "%-15s\t%s\n", lp_name(i), lp_comment(i));
+			io_printf(fd, "%-15s\t%s\n", lp_name(i), lp_comment(i));
 
-	if (remote_version >= 25)
+	if (protocol_version >= 25)
 		io_printf(fd,"@RSYNCD: EXIT\n");
 }
 
 /* this is called when a connection is established to a client
    and we want to start talking. The setup of the system is done from
    here */
 int start_daemon(int f_in, int f_out)
 {
 	char line[200];
 	char *motd;
 	int i = -1;
 	extern char *config_file;
-	extern int remote_version;
 	extern int am_server;
 
 	if (!lp_load(config_file, 0)) {
 		exit_cleanup(RERR_SYNTAX);
 	}
 
