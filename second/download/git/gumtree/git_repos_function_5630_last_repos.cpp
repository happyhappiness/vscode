static int run_receive_hook(struct command *commands,
			    const char *hook_name,
			    int skip_broken,
			    const struct string_list *push_options)
{
	struct receive_hook_feed_state state;
	int status;

	strbuf_init(&state.buf, 0);
	state.cmd = commands;
	state.skip_broken = skip_broken;
	if (feed_receive_hook(&state, NULL, NULL))
		return 0;
	state.cmd = commands;
	state.push_options = push_options;
	status = run_and_feed_hook(hook_name, feed_receive_hook, &state);
	strbuf_release(&state.buf);
	return status;
}