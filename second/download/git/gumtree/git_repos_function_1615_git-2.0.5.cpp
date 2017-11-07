static int path_matches(const char *pathname, int pathlen,
			int basename_offset,
			const struct pattern *pat,
			const char *base, int baselen)
{
	const char *pattern = pat->pattern;
	int prefix = pat->nowildcardlen;
	int isdir = (pathlen && pathname[pathlen - 1] == '/');

	if ((pat->flags & EXC_FLAG_MUSTBEDIR) && !isdir)
		return 0;

	if (pat->flags & EXC_FLAG_NODIR) {
		return match_basename(pathname + basename_offset,
				      pathlen - basename_offset - isdir,
				      pattern, prefix,
				      pat->patternlen, pat->flags);
	}
	return match_pathname(pathname, pathlen - isdir,
			      base, baselen,
			      pattern, prefix, pat->patternlen, pat->flags);
}