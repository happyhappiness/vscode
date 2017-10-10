 	subdir = setup_git_directory_gently(&unused_nongit);
 
 	alias_command = (*argv)[0];
 	alias_string = alias_lookup(alias_command);
 	if (alias_string) {
 		if (alias_string[0] == '!') {
-			const char **alias_argv;
-			int argc = *argcp, i;
+			struct child_process child = CHILD_PROCESS_INIT;
 
 			commit_pager_choice();
 
-			/* build alias_argv */
-			alias_argv = xmalloc(sizeof(*alias_argv) * (argc + 1));
-			alias_argv[0] = alias_string + 1;
-			for (i = 1; i < argc; ++i)
-				alias_argv[i] = (*argv)[i];
-			alias_argv[argc] = NULL;
+			child.use_shell = 1;
+			argv_array_push(&child.args, alias_string + 1);
+			argv_array_pushv(&child.args, (*argv) + 1);
 
-			ret = run_command_v_opt(alias_argv, RUN_USING_SHELL);
+			ret = run_command(&child);
 			if (ret >= 0)   /* normal exit */
 				exit(ret);
 
 			die_errno("While expanding alias '%s': '%s'",
 			    alias_command, alias_string + 1);
 		}
