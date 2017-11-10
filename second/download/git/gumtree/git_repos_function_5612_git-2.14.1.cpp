static int run_and_feed_hook(const char *hook_name, feed_fn feed,
			     struct receive_hook_feed_state *feed_state)
{
	struct child_process proc = CHILD_PROCESS_INIT;
	struct async muxer;
	const char *argv[2];
	int code;

	argv[0] = find_hook(hook_name);
	if (!argv[0])
		return 0;

	argv[1] = NULL;

	proc.argv = argv;
	proc.in = -1;
	proc.stdout_to_stderr = 1;
	if (feed_state->push_options) {
		int i;
		for (i = 0; i < feed_state->push_options->nr; i++)
			argv_array_pushf(&proc.env_array,
				"GIT_PUSH_OPTION_%d=%s", i,
				feed_state->push_options->items[i].string);
		argv_array_pushf(&proc.env_array, "GIT_PUSH_OPTION_COUNT=%d",
				 feed_state->push_options->nr);
	} else
		argv_array_pushf(&proc.env_array, "GIT_PUSH_OPTION_COUNT");

	if (tmp_objdir)
		argv_array_pushv(&proc.env_array, tmp_objdir_env(tmp_objdir));

	if (use_sideband) {
		memset(&muxer, 0, sizeof(muxer));
		muxer.proc = copy_to_sideband;
		muxer.in = -1;
		code = start_async(&muxer);
		if (code)
			return code;
		proc.err = muxer.in;
	}

	prepare_push_cert_sha1(&proc);

	code = start_command(&proc);
	if (code) {
		if (use_sideband)
			finish_async(&muxer);
		return code;
	}

	sigchain_push(SIGPIPE, SIG_IGN);

	while (1) {
		const char *buf;
		size_t n;
		if (feed(feed_state, &buf, &n))
			break;
		if (write_in_full(proc.in, buf, n) != n)
			break;
	}
	close(proc.in);
	if (use_sideband)
		finish_async(&muxer);

	sigchain_pop(SIGPIPE);

	return finish_command(&proc);
}