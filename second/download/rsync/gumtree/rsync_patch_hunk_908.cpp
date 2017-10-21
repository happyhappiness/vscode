 			tmpdir = NULL;
 		}
 	}
 
 	io_printf(f_out, "@RSYNCD: OK\n");
 
-	opt_cnt = read_args(f_in, name, line, sizeof line, rl_nulls, &argv, &argc, &request);
+	read_args(f_in, name, line, sizeof line, rl_nulls, &argv, &argc, &request);
+	orig_argv = argv;
+
+	verbose = 0; /* future verbosity is controlled by client options */
+	ret = parse_arguments(&argc, (const char ***) &argv);
+	if (protect_args && ret) {
+		orig_early_argv = orig_argv;
+		protect_args = 2;
+		read_args(f_in, name, line, sizeof line, 1, &argv, &argc, &request);
+		orig_argv = argv;
+		ret = parse_arguments(&argc, (const char ***) &argv);
+	} else
+		orig_early_argv = NULL;
 
 	if (pre_exec_pid) {
 		err_msg = finish_pre_exec(pre_exec_pid, pre_exec_fd, request,
-					  opt_cnt, argv);
+					  orig_early_argv, orig_argv);
 	}
 
-	verbose = 0; /* future verbosity is controlled by client options */
-	ret = parse_arguments(&argc, (const char ***) &argv, 0);
+	if (orig_early_argv)
+		free(orig_early_argv);
+
 	am_server = 1; /* Don't let someone try to be tricky. */
+	quiet = 0;
 	if (lp_ignore_errors(module_id))
 		ignore_errors = 1;
 	if (write_batch < 0)
 		dry_run = 1;
 
-	if (lp_fake_super(i))
+	if (lp_fake_super(i)) {
+		if (preserve_xattrs > 1)
+			preserve_xattrs = 1;
 		am_root = -1;
-	else if (am_root < 0) /* Treat --fake-super from client as --super. */
+	} else if (am_root < 0) /* Treat --fake-super from client as --super. */
 		am_root = 2;
 
 	if (filesfrom_fd == 0)
 		filesfrom_fd = f_in;
 
 	if (request) {
