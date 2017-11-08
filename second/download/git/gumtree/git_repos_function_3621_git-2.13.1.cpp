static void submodule_reset_index(const char *path)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	prepare_submodule_repo_env_no_git_dir(&cp.env_array);

	cp.git_cmd = 1;
	cp.no_stdin = 1;
	cp.dir = path;

	argv_array_pushf(&cp.args, "--super-prefix=%s%s/",
				   get_super_prefix_or_empty(), path);
	argv_array_pushl(&cp.args, "read-tree", "-u", "--reset", NULL);

	argv_array_push(&cp.args, EMPTY_TREE_SHA1_HEX);

	if (run_command(&cp))
		die("could not reset submodule index");
}