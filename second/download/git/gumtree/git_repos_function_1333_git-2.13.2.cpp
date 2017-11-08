static int apply_option_parse_p(const struct option *opt,
				const char *arg,
				int unset)
{
	struct apply_state *state = opt->value;
	state->p_value = atoi(arg);
	state->p_value_known = 1;
	return 0;
}