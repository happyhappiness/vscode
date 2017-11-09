int git_parse_ulong(const char *value, unsigned long *ret)
{
	uintmax_t tmp;
	if (!git_parse_unsigned(value, &tmp, maximum_unsigned_value_of_type(long)))
		return 0;
	*ret = tmp;
	return 1;
}