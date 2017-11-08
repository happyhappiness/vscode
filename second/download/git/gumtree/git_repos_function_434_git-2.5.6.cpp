static int git_parse_unsigned(const char *value, uintmax_t *ret, uintmax_t max)
{
	if (value && *value) {
		char *end;
		uintmax_t val;
		uintmax_t oldval;

		errno = 0;
		val = strtoumax(value, &end, 0);
		if (errno == ERANGE)
			return 0;
		oldval = val;
		if (!parse_unit_factor(end, &val)) {
			errno = EINVAL;
			return 0;
		}
		if (val > max || oldval > val) {
			errno = ERANGE;
			return 0;
		}
		*ret = val;
		return 1;
	}
	errno = EINVAL;
	return 0;
}