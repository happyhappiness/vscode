 	}
 
 	if (protocol_version >= 25)
 		io_printf(fd,"@RSYNCD: EXIT\n");
 }
 
+static int load_config(int globals_only)
+{
+	if (!config_file) {
+		if (am_server && am_root <= 0)
+			config_file = RSYNCD_USERCONF;
+		else
+			config_file = RSYNCD_SYSCONF;
+	}
+	return lp_load(config_file, globals_only);
+}
+
 /* this is called when a connection is established to a client
    and we want to start talking. The setup of the system is done from
    here */
 int start_daemon(int f_in, int f_out)
 {
 	char line[1024];
