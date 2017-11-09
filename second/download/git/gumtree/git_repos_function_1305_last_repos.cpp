int init_apply_state(struct apply_state *state,
		     const char *prefix,
		     struct lock_file *lock_file)
{
	memset(state, 0, sizeof(*state));
	state->prefix = prefix;
	state->lock_file = lock_file;
	state->newfd = -1;
	state->apply = 1;
	state->line_termination = '\n';
	state->p_value = 1;
	state->p_context = UINT_MAX;
	state->squelch_whitespace_errors = 5;
	state->ws_error_action = warn_on_ws_error;
	state->ws_ignore_action = ignore_ws_none;
	state->linenr = 1;
	string_list_init(&state->fn_table, 0);
	string_list_init(&state->limit_by_name, 0);
	string_list_init(&state->symlink_changes, 0);
	strbuf_init(&state->root, 0);

	git_apply_config();
	if (apply_default_whitespace && parse_whitespace_option(state, apply_default_whitespace))
		return -1;
	if (apply_default_ignorewhitespace && parse_ignorewhitespace_option(state, apply_default_ignorewhitespace))
		return -1;
	return 0;
}