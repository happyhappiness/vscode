static int option_parse_recurse_submodules(const struct option *opt,
				   const char *arg, int unset)
{
	if (unset) {
		recurse_submodules = RECURSE_SUBMODULES_OFF;
	} else {
		if (arg)
			recurse_submodules = parse_fetch_recurse_submodules_arg(opt->long_name, arg);
		else
			recurse_submodules = RECURSE_SUBMODULES_ON;
	}
	return 0;
}