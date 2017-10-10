	return !!errs;
}

static int option_parse_recurse_submodules(const struct option *opt,
				   const char *arg, int unset)
{
	int *flags = opt->value;

	if (*flags & (TRANSPORT_RECURSE_SUBMODULES_CHECK |
		      TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND))
		die("%s can only be used once.", opt->long_name);

	if (arg) {
		if (!strcmp(arg, "check"))
			*flags |= TRANSPORT_RECURSE_SUBMODULES_CHECK;
		else if (!strcmp(arg, "on-demand"))
			*flags |= TRANSPORT_RECURSE_SUBMODULES_ON_DEMAND;
		else
			die("bad %s argument: %s", opt->long_name, arg);
	} else
		die("option %s needs an argument (check|on-demand)",
				opt->long_name);

	return 0;
}

static void set_push_cert_flags(int *flags, int v)
{
