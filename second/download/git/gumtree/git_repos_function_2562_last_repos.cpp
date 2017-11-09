const char *skip_range_arg(const char *arg)
{
	if (*arg == ':' || (*arg == '^' && *(arg + 1) == ':'))
		return parse_range_funcname(arg, NULL, NULL, 0, 0, NULL, NULL, NULL);

	arg = parse_loc(arg, NULL, NULL, 0, -1, NULL);

	if (*arg == ',')
		arg = parse_loc(arg+1, NULL, NULL, 0, 0, NULL);

	return arg;
}