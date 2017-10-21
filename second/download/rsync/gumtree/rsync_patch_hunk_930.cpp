 
 	if (remove_source_files == 1)
 		args[ac++] = "--remove-source-files";
 	else if (remove_source_files)
 		args[ac++] = "--remove-sent-files";
 
+	if (ac > MAX_SERVER_ARGS) { /* Not possible... */
+		rprintf(FERROR, "argc overflow in server_options().\n");
+		exit_cleanup(RERR_MALLOC);
+	}
+
 	*argc_p = ac;
 	return;
 
     oom:
 	out_of_memory("server_options");
 }
