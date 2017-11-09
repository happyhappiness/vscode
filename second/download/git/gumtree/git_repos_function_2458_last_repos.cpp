int match_pathspec(const struct pathspec *ps,
		   const char *name, int namelen,
		   int prefix, char *seen, int is_dir)
{
	int positive, negative;
	unsigned flags = is_dir ? DO_MATCH_DIRECTORY : 0;
	positive = do_match_pathspec(ps, name, namelen,
				     prefix, seen, flags);
	if (!(ps->magic & PATHSPEC_EXCLUDE) || !positive)
		return positive;
	negative = do_match_pathspec(ps, name, namelen,
				     prefix, seen,
				     flags | DO_MATCH_EXCLUDE);
	return negative ? 0 : positive;
}