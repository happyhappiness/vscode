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