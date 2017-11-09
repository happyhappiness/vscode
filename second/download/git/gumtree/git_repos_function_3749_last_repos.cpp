static int submodule_has_commits(const char *path, struct oid_array *commits)
{
	int has_commit = 1;

	/*
	 * Perform a cheap, but incorrect check for the existence of 'commits'.
	 * This is done by adding the submodule's object store to the in-core
	 * object store, and then querying for each commit's existence.  If we
	 * do not have the commit object anywhere, there is no chance we have
	 * it in the object store of the correct submodule and have it
	 * reachable from a ref, so we can fail early without spawning rev-list
	 * which is expensive.
	 */
	if (add_submodule_odb(path))
		return 0;

	oid_array_for_each_unique(commits, check_has_commit, &has_commit);

	if (has_commit) {
		/*
		 * Even if the submodule is checked out and the commit is
		 * present, make sure it exists in the submodule's object store
		 * and that it is reachable from a ref.
		 */
		struct child_process cp = CHILD_PROCESS_INIT;
		struct strbuf out = STRBUF_INIT;

		argv_array_pushl(&cp.args, "rev-list", "-n", "1", NULL);
		oid_array_for_each_unique(commits, append_oid_to_argv, &cp.args);
		argv_array_pushl(&cp.args, "--not", "--all", NULL);

		prepare_submodule_repo_env(&cp.env_array);
		cp.git_cmd = 1;
		cp.no_stdin = 1;
		cp.dir = path;

		if (capture_command(&cp, &out, GIT_MAX_HEXSZ + 1) || out.len)
			has_commit = 0;

		strbuf_release(&out);
	}

	return has_commit;
}