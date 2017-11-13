static int submodule_has_dirty_index(const struct submodule *sub)
{
	struct child_process cp = CHILD_PROCESS_INIT;

	prepare_submodule_repo_env_no_git_dir(&cp.env_array);

	cp.git_cmd = 1;
	argv_array_pushl(&cp.args, "diff-index", "--quiet",
				   "--cached", "HEAD", NULL);
	cp.no_stdin = 1;
	cp.no_stdout = 1;
	cp.dir = sub->path;
	if (start_command(&cp))
		die("could not recurse into submodule '%s'", sub->path);

	return finish_command(&cp);
}