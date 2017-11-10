static int option_parse_z(const struct option *opt,
			  const char *arg, int unset)
{
	if (unset)
		line_termination = '\n';
	else
		line_termination = 0;
	return 0;
}