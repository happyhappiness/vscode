static int exclude_existing_callback(const struct option *opt, const char *arg,
				     int unset)
{
	exclude_arg = 1;
	*(const char **)opt->value = arg;
	return 0;
}