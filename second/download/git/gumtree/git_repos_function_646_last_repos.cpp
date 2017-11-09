static int git_parse_int64(const char *value, int64_t *ret)
{
	intmax_t tmp;
	if (!git_parse_signed(value, &tmp, maximum_signed_value_of_type(int64_t)))
		return 0;
	*ret = tmp;
	return 1;
}