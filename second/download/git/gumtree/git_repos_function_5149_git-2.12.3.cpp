static int run_post_rewrite_hook(const struct am_state *state)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	const char *hook = find_hook("post-rewrite");
	int ret;

	if (!hook)
		return 0;

	argv_array_push(&cp.args, hook);
	argv_array_push(&cp.args, "rebase");

	cp.in = xopen(am_path(state, "rewritten"), O_RDONLY);
	cp.stdout_to_stderr = 1;

	ret = run_command(&cp);

	close(cp.in);
	return ret;
}