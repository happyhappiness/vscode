static int is_fixed(const char *s, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++) {
		if (is_regex_special(s[i]))
			return 0;
	}

	return 1;
}