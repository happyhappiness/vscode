static int handle_alias(int *argcp, const char ***argv)
{
	int envchanged = 0, ret = 0, saved_errno = errno;
	const char *subdir;
	int count, option_count;
	const char **new_argv;
	const char *alias_command;
	char *alias_string;
	int unused_nongit;

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
		count = split_cmdline(alias_string, &new_argv);
		if (count < 0)
			die("Bad alias.%s string: %s", alias_command,
			    split_cmdline_strerror(count));
		option_count = handle_options(&new_argv, &count, &envchanged);
		if (envchanged)
			die("alias '%s' changes environment variables\n"
				 "You can use '!git' in the alias to do this.",
				 alias_command);
		memmove(new_argv - option_count, new_argv,
				count * sizeof(char *));
		new_argv -= option_count;

		if (count < 1)
			die("empty alias for %s", alias_command);

		if (!strcmp(alias_command, new_argv[0]))
			die("recursive alias: %s", alias_command);

		trace_argv_printf(new_argv,
				  "trace: alias expansion: %s =>",
				  alias_command);

		REALLOC_ARRAY(new_argv, count + *argcp);
		/* insert after command name */
		memcpy(new_argv + count, *argv + 1, sizeof(char *) * *argcp);

		*argv = new_argv;
		*argcp += count - 1;

		ret = 1;
	}

	if (subdir && chdir(subdir))
		die_errno("Cannot change to '%s'", subdir);

	errno = saved_errno;

	return ret;
}