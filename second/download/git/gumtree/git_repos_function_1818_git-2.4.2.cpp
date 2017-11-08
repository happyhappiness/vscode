static struct exclude *last_exclude_matching_from_list(const char *pathname,
						       int pathlen,
						       const char *basename,
						       int *dtype,
						       struct exclude_list *el)
{
	int i;

	if (!el->nr)
		return NULL;	/* undefined */

	for (i = el->nr - 1; 0 <= i; i--) {
		struct exclude *x = el->excludes[i];
		const char *exclude = x->pattern;
		int prefix = x->nowildcardlen;

		if (x->flags & EXC_FLAG_MUSTBEDIR) {
			if (*dtype == DT_UNKNOWN)
				*dtype = get_dtype(NULL, pathname, pathlen);
			if (*dtype != DT_DIR)
				continue;
		}

		if (x->flags & EXC_FLAG_NODIR) {
			if (match_basename(basename,
					   pathlen - (basename - pathname),
					   exclude, prefix, x->patternlen,
					   x->flags))
				return x;
			continue;
		}

		assert(x->baselen == 0 || x->base[x->baselen - 1] == '/');
		if (match_pathname(pathname, pathlen,
				   x->base, x->baselen ? x->baselen - 1 : 0,
				   exclude, prefix, x->patternlen, x->flags))
			return x;
	}
	return NULL; /* undecided */
}