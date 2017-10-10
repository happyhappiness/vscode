	subdir = setup_git_directory_gently(&unused_nongit);

	alias_command = (*argv)[0];
	alias_string = alias_lookup(alias_command);
	if (alias_string) {
		if (alias_string[0] == '!') {
			struct child_process child = CHILD_PROCESS_INIT;

			commit_pager_choice();

			child.use_shell = 1;
			argv_array_push(&child.args, alias_string + 1);
			argv_array_pushv(&child.args, (*argv) + 1);

			ret = run_command(&child);
			if (ret >= 0)   /* normal exit */
				exit(ret);

			die_errno("While expanding alias '%s': '%s'",
			    alias_command, alias_string + 1);
		}
