static int option_parse_n(const struct option *opt,
			  const char *arg, int unset)
{
	show_diffstat = unset;
	return 0;
}