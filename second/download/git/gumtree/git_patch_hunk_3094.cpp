 	fflush(stdout);
 	strbuf_reset(buf);
 }
 
 static int push_dav(int nr_spec, char **specs)
 {
-	const char **argv = xmalloc((10 + nr_spec) * sizeof(char*));
-	int argc = 0, i;
+	struct child_process child = CHILD_PROCESS_INIT;
+	size_t i;
 
-	argv[argc++] = "http-push";
-	argv[argc++] = "--helper-status";
+	child.git_cmd = 1;
+	argv_array_push(&child.args, "http-push");
+	argv_array_push(&child.args, "--helper-status");
 	if (options.dry_run)
-		argv[argc++] = "--dry-run";
+		argv_array_push(&child.args, "--dry-run");
 	if (options.verbosity > 1)
-		argv[argc++] = "--verbose";
-	argv[argc++] = url.buf;
+		argv_array_push(&child.args, "--verbose");
+	argv_array_push(&child.args, url.buf);
 	for (i = 0; i < nr_spec; i++)
-		argv[argc++] = specs[i];
-	argv[argc++] = NULL;
+		argv_array_push(&child.args, specs[i]);
 
-	if (run_command_v_opt(argv, RUN_GIT_CMD))
-		die("git-%s failed", argv[0]);
-	free(argv);
+	if (run_command(&child))
+		die("git-http-push failed");
 	return 0;
 }
 
 static int push_git(struct discovery *heads, int nr_spec, char **specs)
 {
 	struct rpc_state rpc;
