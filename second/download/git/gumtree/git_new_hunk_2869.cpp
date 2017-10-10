	return !!errs;
}

static int option_parse_recurse_submodules(const struct option *opt,
				   const char *arg, int unset)
{
	int *recurse_submodules = opt->value;

	if (unset)
		*recurse_submodules = RECURSE_SUBMODULES_OFF;
	else if (arg)
		*recurse_submodules = parse_push_recurse_submodules_arg(opt->long_name, arg);
	else
		die("%s missing parameter", opt->long_name);

	return 0;
}

static void set_push_cert_flags(int *flags, int v)
{
