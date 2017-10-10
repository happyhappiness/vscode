 		exit(run_builtin(builtin, argc, argv));
 	argv_array_clear(&args);
 }
 
 static void execv_dashed_external(const char **argv)
 {
-	struct strbuf cmd = STRBUF_INIT;
-	const char *tmp;
+	struct child_process cmd = CHILD_PROCESS_INIT;
 	int status;
 
 	if (get_super_prefix())
 		die("%s doesn't support --super-prefix", argv[0]);
 
 	if (use_pager == -1)
 		use_pager = check_pager_config(argv[0]);
 	commit_pager_choice();
 
-	strbuf_addf(&cmd, "git-%s", argv[0]);
+	argv_array_pushf(&cmd.args, "git-%s", argv[0]);
+	argv_array_pushv(&cmd.args, argv + 1);
+	cmd.clean_on_exit = 1;
+	cmd.wait_after_clean = 1;
+	cmd.silent_exec_failure = 1;
 
-	/*
-	 * argv[0] must be the git command, but the argv array
-	 * belongs to the caller, and may be reused in
-	 * subsequent loop iterations. Save argv[0] and
-	 * restore it on error.
-	 */
-	tmp = argv[0];
-	argv[0] = cmd.buf;
-
-	trace_argv_printf(argv, "trace: exec:");
+	trace_argv_printf(cmd.args.argv, "trace: exec:");
 
 	/*
-	 * if we fail because the command is not found, it is
-	 * OK to return. Otherwise, we just pass along the status code.
+	 * If we fail because the command is not found, it is
+	 * OK to return. Otherwise, we just pass along the status code,
+	 * or our usual generic code if we were not even able to exec
+	 * the program.
 	 */
-	status = run_command_v_opt(argv, RUN_SILENT_EXEC_FAILURE | RUN_CLEAN_ON_EXIT);
-	if (status >= 0 || errno != ENOENT)
+	status = run_command(&cmd);
+	if (status >= 0)
 		exit(status);
-
-	argv[0] = tmp;
-
-	strbuf_release(&cmd);
+	else if (errno != ENOENT)
+		exit(128);
 }
 
 static int run_argv(int *argcp, const char ***argv)
 {
 	int done_alias = 0;
 
