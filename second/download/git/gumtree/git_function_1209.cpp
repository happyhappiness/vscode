static int decorate_callback(const struct option *opt, const char *arg, int unset)
{
	if (unset)
		decoration_style = 0;
	else if (arg)
		decoration_style = parse_decoration_style("command line", arg);
	else
		decoration_style = DECORATE_SHORT_REFS;

	if (decoration_style < 0)
		die("invalid --decorate option: %s", arg);

	decoration_given = 1;

	return 0;
}