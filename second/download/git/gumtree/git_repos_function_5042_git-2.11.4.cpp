static void show_gitlink(const struct cache_entry *ce)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	int status;
	int i;

	argv_array_pushf(&cp.args, "--super-prefix=%s%s/",
			 super_prefix ? super_prefix : "",
			 ce->name);
	argv_array_push(&cp.args, "ls-files");
	argv_array_push(&cp.args, "--recurse-submodules");

	/* add supported options */
	argv_array_pushv(&cp.args, submodules_options.argv);

	/*
	 * Pass in the original pathspec args.  The submodule will be
	 * responsible for prepending the 'submodule_prefix' prior to comparing
	 * against the pathspec for matches.
	 */
	argv_array_push(&cp.args, "--");
	for (i = 0; i < pathspec.nr; i++)
		argv_array_push(&cp.args, pathspec.items[i].original);

	cp.git_cmd = 1;
	cp.dir = ce->name;
	status = run_command(&cp);
	if (status)
		exit(status);
}