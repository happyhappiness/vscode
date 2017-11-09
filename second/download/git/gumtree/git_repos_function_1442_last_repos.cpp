static int apply_option_parse_space_change(const struct option *opt,
					   const char *arg, int unset)
{
	struct apply_state *state = opt->value;
	if (unset)
		state->ws_ignore_action = ignore_ws_none;
	else
		state->ws_ignore_action = ignore_ws_change;
	return 0;
}