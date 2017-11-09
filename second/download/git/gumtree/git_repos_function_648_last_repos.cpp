static int git_parse_ssize_t(const char *value, ssize_t *ret)
{
	intmax_t tmp;
	if (!git_parse_signed(value, &tmp, maximum_signed_value_of_type(ssize_t)))
		return 0;
	*ret = tmp;
	return 1;
}