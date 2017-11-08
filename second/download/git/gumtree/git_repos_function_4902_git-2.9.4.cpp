static int run_apply(const struct am_state *state, const char *index_file)
{
	struct child_process cp = CHILD_PROCESS_INIT;

	cp.git_cmd = 1;

	if (index_file)
		argv_array_pushf(&cp.env_array, "GIT_INDEX_FILE=%s", index_file);

	/*
	 * If we are allowed to fall back on 3-way merge, don't give false
	 * errors during the initial attempt.
	 */
	if (state->threeway && !index_file) {
		cp.no_stdout = 1;
		cp.no_stderr = 1;
	}

	argv_array_push(&cp.args, "apply");

	argv_array_pushv(&cp.args, state->git_apply_opts.argv);

	if (index_file)
		argv_array_push(&cp.args, "--cached");
	else
		argv_array_push(&cp.args, "--index");

	argv_array_push(&cp.args, am_path(state, "patch"));

	if (run_command(&cp))
		return -1;

	/* Reload index as git-apply will have modified it. */
	discard_cache();
	read_cache_from(index_file ? index_file : get_index_file());

	return 0;
}