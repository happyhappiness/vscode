 
 	io_printf(f_out, "@RSYNCD: OK\n");
 
 	read_args(f_in, name, line, sizeof line, rl_nulls, &argv, &argc, &request);
 	orig_argv = argv;
 
-	verbose = 0; /* future verbosity is controlled by client options */
+	save_munge_symlinks = munge_symlinks;
+
+	reset_output_levels(); /* future verbosity is controlled by client options */
 	ret = parse_arguments(&argc, (const char ***) &argv);
 	if (protect_args && ret) {
 		orig_early_argv = orig_argv;
 		protect_args = 2;
 		read_args(f_in, name, line, sizeof line, 1, &argv, &argc, &request);
 		orig_argv = argv;
 		ret = parse_arguments(&argc, (const char ***) &argv);
 	} else
 		orig_early_argv = NULL;
 
+	munge_symlinks = save_munge_symlinks; /* The client mustn't control this. */
+
 	if (pre_exec_pid) {
-		err_msg = finish_pre_exec(pre_exec_pid, pre_exec_fd, request,
-					  orig_early_argv, orig_argv);
+		err_msg = finish_pre_exec(pre_exec_pid, pre_exec_arg_fd, pre_exec_error_fd,
+					  request, orig_early_argv, orig_argv);
 	}
 
 	if (orig_early_argv)
 		free(orig_early_argv);
 
 	am_server = 1; /* Don't let someone try to be tricky. */
