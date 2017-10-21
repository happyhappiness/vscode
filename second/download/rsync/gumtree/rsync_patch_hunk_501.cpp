 	char line[200];
 	char *motd;
 	int i = -1;
 	extern char *config_file;
 	extern int remote_version;
 
-	if (!lp_load(config_file)) {
+	if (!lp_load(config_file, 0)) {
 		exit_cleanup(1);
 	}
 
 	set_socket_options(fd,"SO_KEEPALIVE");
 
 	io_printf(fd,"@RSYNCD: %d\n", PROTOCOL_VERSION);
