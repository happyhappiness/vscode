static int has_null(const char *s, size_t len)
{
	/*
	 * regcomp cannot accept patterns with NULs so when using it
	 * we consider any pattern containing a NUL fixed.
	 */
	if (memchr(s, 0, len))
		return 1;

	return 0;
}