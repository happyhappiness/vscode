	negative = do_match_pathspec(ps, name, namelen,
				     prefix, seen,
				     flags | DO_MATCH_EXCLUDE);
	return negative ? 0 : positive;
}

/*
 * Return the length of the "simple" part of a path match limiter.
 */
int simple_length(const char *match)
{
	int len = -1;
