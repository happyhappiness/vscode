static int apply_option_parse_whitespace(const struct option *opt,
					 const char *arg, int unset)
{
	struct apply_state *state = opt->value;
	state->whitespace_option = arg;
	if (parse_whitespace_option(state, arg))
		exit(1);
	return 0;
}