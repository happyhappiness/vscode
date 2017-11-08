int parse_opt_color_flag_cb(const struct option *opt, const char *arg,
			    int unset)
{
	int value;

	if (!arg)
		arg = unset ? "never" : (const char *)opt->defval;
	value = git_config_colorbool(NULL, arg);
	if (value < 0)
		return opterror(opt,
			"expects \"always\", \"auto\", or \"never\"", 0);
	*(int *)opt->value = value;
	return 0;
}