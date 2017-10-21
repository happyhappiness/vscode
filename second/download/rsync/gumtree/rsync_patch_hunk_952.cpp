 		while (remote_argc > 0) {
 			if (argc >= MAX_ARGS - 1) {
 			  arg_overflow:
 				rprintf(FERROR, "internal: args[] overflowed in do_cmd()\n");
 				exit_cleanup(RERR_SYNTAX);
 			}
-			args[argc++] = *remote_argv++;
+			if (**remote_argv == '-') {
+				if (asprintf(args + argc++, "./%s", *remote_argv++) < 0)
+					out_of_memory("do_cmd");
+			} else
+				args[argc++] = *remote_argv++;
 			remote_argc--;
 		}
 	}
 
 	args[argc] = NULL;
 
