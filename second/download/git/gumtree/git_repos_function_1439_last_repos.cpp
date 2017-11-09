static int apply_option_parse_exclude(const struct option *opt,
				      const char *arg, int unset)
{
	struct apply_state *state = opt->value;
	add_name_limit(state, arg, 1);
	return 0;
}