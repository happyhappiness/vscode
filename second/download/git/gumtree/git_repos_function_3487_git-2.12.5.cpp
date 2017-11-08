static int push_submodule(const char *path, int dry_run)
{
	if (add_submodule_odb(path))
		return 1;

	if (for_each_remote_ref_submodule(path, has_remote, NULL) > 0) {
		struct child_process cp = CHILD_PROCESS_INIT;
		argv_array_push(&cp.args, "push");
		if (dry_run)
			argv_array_push(&cp.args, "--dry-run");

		prepare_submodule_repo_env(&cp.env_array);
		cp.git_cmd = 1;
		cp.no_stdin = 1;
		cp.dir = path;
		if (run_command(&cp))
			return 0;
		close(cp.out);
	}

	return 1;
}