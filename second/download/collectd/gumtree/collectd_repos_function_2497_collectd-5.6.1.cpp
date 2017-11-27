long global_option_get_long (const char *option, long default_value)
{
	const char *str;
	long value;

	str = global_option_get (option);
	if (NULL == str)
		return (default_value);

	errno = 0;
	value = strtol (str, /* endptr = */ NULL, /* base = */ 0);
	if (errno != 0)
		return (default_value);

	return (value);
}