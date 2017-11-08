static int build_fake_ancestor(const struct am_state *state, const char *index_file)
{
	struct child_process cp = CHILD_PROCESS_INIT;

	cp.git_cmd = 1;
	argv_array_push(&cp.args, "apply");
	argv_array_pushv(&cp.args, state->git_apply_opts.argv);
	argv_array_pushf(&cp.args, "--build-fake-ancestor=%s", index_file);
	argv_array_push(&cp.args, am_path(state, "patch"));

	if (run_command(&cp))
		return -1;

	return 0;
}