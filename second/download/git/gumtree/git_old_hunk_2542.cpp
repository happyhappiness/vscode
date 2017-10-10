		if (arg)
			unpack_unreachable_expiration = approxidate(arg);
	}
	return 0;
}

static int option_parse_ulong(const struct option *opt,
			      const char *arg, int unset)
{
	if (unset)
		die(_("option %s does not accept negative form"),
		    opt->long_name);

	if (!git_parse_ulong(arg, opt->value))
		die(_("unable to parse value '%s' for option %s"),
		    arg, opt->long_name);
	return 0;
}

#define OPT_ULONG(s, l, v, h) \
	{ OPTION_CALLBACK, (s), (l), (v), "n", (h),	\
	  PARSE_OPT_NONEG, option_parse_ulong }

int cmd_pack_objects(int argc, const char **argv, const char *prefix)
{
	int use_internal_rev_list = 0;
	int thin = 0;
	int shallow = 0;
	int all_progress_implied = 0;
