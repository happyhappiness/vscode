static int option_parse_prefix(const struct option *opt,
			       const char *arg, int unset)
{
	state.base_dir = arg;
	state.base_dir_len = strlen(arg);
	return 0;
}