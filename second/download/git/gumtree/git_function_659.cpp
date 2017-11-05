static int do_exec(const char *command_line)
{
	const char *child_argv[] = { NULL, NULL };
	int dirty, status;

	fprintf(stderr, "Executing: %s\n", command_line);
	child_argv[0] = command_line;
	status = run_command_v_opt(child_argv, RUN_USING_SHELL);

	/* force re-reading of the cache */
	if (discard_cache() < 0 || read_cache() < 0)
		return error(_("could not read index"));

	dirty = require_clean_work_tree("rebase", NULL, 1, 1);

	if (status) {
		warning(_("execution failed: %s\n%s"
			  "You can fix the problem, and then run\n"
			  "\n"
			  "  git rebase --continue\n"
			  "\n"),
			command_line,
			dirty ? N_("and made changes to the index and/or the "
				"working tree\n") : "");
		if (status == 127)
			/* command not found */
			status = 1;
	} else if (dirty) {
		warning(_("execution succeeded: %s\nbut "
			  "left changes to the index and/or the working tree\n"
			  "Commit or stash your changes, and then run\n"
			  "\n"
			  "  git rebase --continue\n"
			  "\n"), command_line);
		status = 1;
	}

	return status;
}