 			open("/dev/null", O_RDWR);
 		}
 
 		return start_daemon(STDIN_FILENO, STDIN_FILENO);
 	}
 
-	if (!lp_load(config_file, 1)) {
+	if (!load_config(1)) {
 		fprintf(stderr, "Failed to parse config file: %s\n", config_file);
 		exit_cleanup(RERR_SYNTAX);
 	}
 
 	if (no_detach)
 		create_pid_file();
