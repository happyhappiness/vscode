int parse_long_opt(const char *opt, const char **argv,
		   const char **optarg)
{
	const char *arg = argv[0];
	if (!skip_prefix(arg, "--", &arg))
		return 0;
	if (!skip_prefix(arg, opt, &arg))
		return 0;
	if (*arg == '=') { /* stuck form: --option=value */
		*optarg = arg + 1;
		return 1;
	}
	if (*arg != '\0')
		return 0;
	/* separate form: --option value */
	if (!argv[1])
		die("Option '--%s' requires a value", opt);
	*optarg = argv[1];
	return 2;
}