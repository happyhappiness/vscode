 			open("/dev/null", O_RDWR);
 		}
 
 		return start_daemon(STDIN_FILENO, STDIN_FILENO);
 	}
 
-	if (!no_detach)
-		become_daemon();
-
-	if (!lp_load(config_file, 1))
+	if (!lp_load(config_file, 1)) {
+		fprintf(stderr, "Failed to parse config file: %s\n", config_file);
 		exit_cleanup(RERR_SYNTAX);
+	}
+
+	if (no_detach)
+		create_pid_file();
+	else
+		become_daemon();
 
 	if (rsync_port == 0 && (rsync_port = lp_rsync_port()) == 0)
 		rsync_port = RSYNC_PORT;
 	if (bind_address == NULL && *lp_bind_address())
 		bind_address = lp_bind_address();
 
