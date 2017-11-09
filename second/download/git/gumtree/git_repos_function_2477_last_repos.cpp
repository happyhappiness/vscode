int match_basename(const char *basename, int basenamelen,
		   const char *pattern, int prefix, int patternlen,
		   unsigned flags)
{
	if (prefix == patternlen) {
		if (patternlen == basenamelen &&
		    !fspathncmp(pattern, basename, basenamelen))
			return 1;
	} else if (flags & EXC_FLAG_ENDSWITH) {
		/* "*literal" matching against "fooliteral" */
		if (patternlen - 1 <= basenamelen &&
		    !fspathncmp(pattern + 1,
				   basename + basenamelen - (patternlen - 1),
				   patternlen - 1))
			return 1;
	} else {
		if (fnmatch_icase_mem(pattern, patternlen,
				      basename, basenamelen,
				      0) == 0)
			return 1;
	}
	return 0;
}