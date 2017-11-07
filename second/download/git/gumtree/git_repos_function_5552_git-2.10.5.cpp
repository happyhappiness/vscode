static int chmod_callback(const struct option *opt,
				const char *arg, int unset)
{
	char *flip = opt->value;
	if ((arg[0] != '-' && arg[0] != '+') || arg[1] != 'x' || arg[2])
		return error("option 'chmod' expects \"+x\" or \"-x\"");
	*flip = arg[0];
	return 0;
}