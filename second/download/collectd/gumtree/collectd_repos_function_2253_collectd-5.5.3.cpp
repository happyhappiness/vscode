int strtogauge (const char *string, gauge_t *ret_value) /* {{{ */
{
	gauge_t tmp;
	char *endptr = NULL;

	if ((string == NULL) || (ret_value == NULL))
		return (EINVAL);

	errno = 0;
	endptr = NULL;
	tmp = (gauge_t) strtod (string, &endptr);
	if (errno != 0)
		return (errno);
	else if ((endptr == NULL) || (*endptr != 0))
		return (EINVAL);

	*ret_value = tmp;
	return (0);
}