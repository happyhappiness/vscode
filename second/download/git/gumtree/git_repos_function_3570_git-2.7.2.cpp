static int is_fixed(const char *s, size_t len)
{
	size_t i;

	/* regcomp cannot accept patterns with NULs so we
	 * consider any pattern containing a NUL fixed.
	 */
	if (memchr(s, 0, len))
		return 1;

	for (i = 0; i < len; i++) {
		if (is_regex_special(s[i]))
			return 0;
	}

	return 1;
}