	return el;
}

/*
 * Used to set up core.excludesfile and .git/info/exclude lists.
 */
void add_excludes_from_file(struct dir_struct *dir, const char *fname)
{
	struct exclude_list *el;
	el = add_exclude_list(dir, EXC_FILE, fname);
	if (add_excludes_from_file_to_list(fname, "", 0, el, 0) < 0)
		die("cannot use %s as an exclude file", fname);
}

int match_basename(const char *basename, int basenamelen,
		   const char *pattern, int prefix, int patternlen,
		   int flags)
{
	if (prefix == patternlen) {
		if (patternlen == basenamelen &&
