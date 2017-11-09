static int excluded_header_field(const char *field, size_t len, const char **exclude)
{
	if (!exclude)
		return 0;

	while (*exclude) {
		size_t xlen = strlen(*exclude);
		if (len == xlen &&
		    !memcmp(field, *exclude, xlen) && field[xlen] == ' ')
			return 1;
		exclude++;
	}
	return 0;
}