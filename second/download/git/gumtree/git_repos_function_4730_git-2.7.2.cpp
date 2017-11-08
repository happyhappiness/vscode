static int option_parse_z(const struct option *opt,
			  const char *arg, int unset)
{
	line_terminator = unset ? '\n' : '\0';

	return 0;
}