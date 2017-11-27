cdtime_t global_option_get_time (const char *name, cdtime_t def) /* {{{ */
{
	char const *optstr;
	char *endptr = NULL;
	double v;

	optstr = global_option_get (name);
	if (optstr == NULL)
		return (def);

	errno = 0;
	v = strtod (optstr, &endptr);
	if ((endptr == NULL) || (*endptr != 0) || (errno != 0))
		return (def);
	else if (v <= 0.0)
		return (def);

	return (DOUBLE_TO_CDTIME_T (v));
}