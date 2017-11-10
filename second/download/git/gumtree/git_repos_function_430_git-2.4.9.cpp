static int git_parse_signed(const char *value, intmax_t *ret, intmax_t max)
{
	if (value && *value) {
		char *end;
		intmax_t val;
		uintmax_t uval;
		uintmax_t factor = 1;

		errno = 0;
		val = strtoimax(value, &end, 0);
		if (errno == ERANGE)
			return 0;
		if (!parse_unit_factor(end, &factor)) {
			errno = EINVAL;
			return 0;
		}
		uval = labs(val);
		uval *= factor;
		if (uval > max || labs(val) > uval) {
			errno = ERANGE;
			return 0;
		}
		val *= factor;
		*ret = val;
		return 1;
	}
	errno = EINVAL;
	return 0;
}