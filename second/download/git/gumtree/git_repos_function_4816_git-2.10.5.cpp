static int option_parse_whitespace(const struct option *opt,
				   const char *arg, int unset)
{
	struct apply_state *state = opt->value;
	state->whitespace_option = arg;
	parse_whitespace_option(state, arg);
	return 0;
}