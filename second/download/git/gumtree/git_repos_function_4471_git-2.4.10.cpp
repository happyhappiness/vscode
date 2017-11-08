static int option_parse_p(const struct option *opt,
			  const char *arg, int unset)
{
	p_value = atoi(arg);
	p_value_known = 1;
	return 0;
}