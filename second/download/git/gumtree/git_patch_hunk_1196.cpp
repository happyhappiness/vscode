 	child.no_stdout = 1;
 	child.no_stderr = 1;
 	argv_array_push(&child.args, "stash");
 	argv_array_push(&child.args, "apply");
 	argv_array_push(&child.args, stash_sha1.buf);
 	if (!run_command(&child))
-		printf(_("Applied autostash.\n"));
+		fprintf(stderr, _("Applied autostash.\n"));
 	else {
 		struct child_process store = CHILD_PROCESS_INIT;
 
 		store.git_cmd = 1;
 		argv_array_push(&store.args, "stash");
 		argv_array_push(&store.args, "store");
