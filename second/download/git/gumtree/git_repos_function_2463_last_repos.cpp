void parse_exclude_pattern(const char **pattern,
			   int *patternlen,
			   unsigned *flags,
			   int *nowildcardlen)
{
	const char *p = *pattern;
	size_t i, len;

	*flags = 0;
	if (*p == '!') {
		*flags |= EXC_FLAG_NEGATIVE;
		p++;
	}
	len = strlen(p);
	if (len && p[len - 1] == '/') {
		len--;
		*flags |= EXC_FLAG_MUSTBEDIR;
	}
	for (i = 0; i < len; i++) {
		if (p[i] == '/')
			break;
	}
	if (i == len)
		*flags |= EXC_FLAG_NODIR;
	*nowildcardlen = simple_length(p);
	/*
	 * we should have excluded the trailing slash from 'p' too,
	 * but that's one more allocation. Instead just make sure
	 * nowildcardlen does not exceed real patternlen
	 */
	if (*nowildcardlen > len)
		*nowildcardlen = len;
	if (*p == '*' && no_wildcard(p + 1))
		*flags |= EXC_FLAG_ENDSWITH;
	*pattern = p;
	*patternlen = len;
}