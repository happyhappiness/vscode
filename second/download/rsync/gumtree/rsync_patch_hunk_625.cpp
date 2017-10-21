 		    io_printf(fd, "%-15s\t%s\n", lp_name(i), lp_comment(i));
 
 	if (remote_version >= 25)
 		io_printf(fd,"@RSYNCD: EXIT\n");
 }
 
-/* this is called when a socket connection is established to a client
+/* this is called when a connection is established to a client
    and we want to start talking. The setup of the system is done from
    here */
-static int start_daemon(int fd)
+int start_daemon(int f_in, int f_out)
 {
 	char line[200];
 	char *motd;
 	int i = -1;
 	extern char *config_file;
 	extern int remote_version;
+	extern int am_server;
 
 	if (!lp_load(config_file, 0)) {
 		exit_cleanup(RERR_SYNTAX);
 	}
 
-	set_socket_options(fd,"SO_KEEPALIVE");
-	set_socket_options(fd,lp_socket_options());
-	set_nonblocking(fd);
+	log_init();
+
+	if (!am_server) {
+		set_socket_options(f_in, "SO_KEEPALIVE");
+		set_socket_options(f_in, lp_socket_options());
+		set_nonblocking(f_in);
+	}
 
-	io_printf(fd,"@RSYNCD: %d\n", PROTOCOL_VERSION);
+	io_printf(f_out, "@RSYNCD: %d\n", PROTOCOL_VERSION);
 
 	motd = lp_motd_file();
 	if (motd && *motd) {
 		FILE *f = fopen(motd,"r");
 		while (f && !feof(f)) {
 			int len = fread(line, 1, sizeof(line)-1, f);
 			if (len > 0) {
 				line[len] = 0;
-				io_printf(fd,"%s", line);
+				io_printf(f_out, "%s", line);
 			}
 		}
 		if (f) fclose(f);
-		io_printf(fd,"\n");
+		io_printf(f_out, "\n");
 	}
 
-	if (!read_line(fd, line, sizeof(line)-1)) {
+	if (!read_line(f_in, line, sizeof(line)-1)) {
 		return -1;
 	}
 
 	if (sscanf(line,"@RSYNCD: %d", &remote_version) != 1) {
-		io_printf(fd,"@ERROR: protocol startup error\n");
+		io_printf(f_out, "@ERROR: protocol startup error\n");
 		return -1;
 	}	
 
 	while (i == -1) {
 		line[0] = 0;
-		if (!read_line(fd, line, sizeof(line)-1)) {
+		if (!read_line(f_in, line, sizeof(line)-1)) {
 			return -1;
 		}
 
 		if (!*line || strcmp(line,"#list")==0) {
-			send_listing(fd);
+			send_listing(f_out);
 			return -1;
 		} 
 
 		if (*line == '#') {
 			/* it's some sort of command that I don't understand */
-			io_printf(fd,"@ERROR: Unknown command '%s'\n", line);
+			io_printf(f_out, "@ERROR: Unknown command '%s'\n", line);
 			return -1;
 		}
 
 		i = lp_number(line);
 		if (i == -1) {
-			io_printf(fd,"@ERROR: Unknown module '%s'\n", line);
+			io_printf(f_out, "@ERROR: Unknown module '%s'\n", line);
 			return -1;
 		}
 	}
 
-	return rsync_module(fd, i);
+	return rsync_module(f_in, f_out, i);
 }
 
 
 int daemon_main(void)
 {
 	extern char *config_file;
