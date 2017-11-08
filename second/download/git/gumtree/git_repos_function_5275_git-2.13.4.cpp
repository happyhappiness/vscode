static void show_gitlink(const struct cache_entry *ce)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	int status;
	char *dir;

	prepare_submodule_repo_env(&cp.env_array);
	argv_array_push(&cp.env_array, GIT_DIR_ENVIRONMENT);

	if (prefix_len)
		argv_array_pushf(&cp.env_array, "%s=%s",
				 GIT_TOPLEVEL_PREFIX_ENVIRONMENT,
				 prefix);
	argv_array_pushf(&cp.args, "--super-prefix=%s%s/",
			 super_prefix ? super_prefix : "",
			 ce->name);
	argv_array_push(&cp.args, "ls-files");
	argv_array_push(&cp.args, "--recurse-submodules");

	/* add supported options */
	argv_array_pushv(&cp.args, submodule_options.argv);

	cp.git_cmd = 1;
	dir = mkpathdup("%s/%s", get_git_work_tree(), ce->name);
	cp.dir = dir;
	status = run_command(&cp);
	free(dir);
	if (status)
		exit(status);
}