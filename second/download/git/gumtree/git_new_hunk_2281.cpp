	return el;
}

/*
 * Used to set up core.excludesfile and .git/info/exclude lists.
 */
static void add_excludes_from_file_1(struct dir_struct *dir, const char *fname,
				     struct sha1_stat *sha1_stat)
{
	struct exclude_list *el;
	/*
	 * catch setup_standard_excludes() that's called before
	 * dir->untracked is assigned. That function behaves
	 * differently when dir->untracked is non-NULL.
	 */
	if (!dir->untracked)
		dir->unmanaged_exclude_files++;
	el = add_exclude_list(dir, EXC_FILE, fname);
	if (add_excludes(fname, "", 0, el, 0, sha1_stat) < 0)
		die("cannot use %s as an exclude file", fname);
}

void add_excludes_from_file(struct dir_struct *dir, const char *fname)
{
	dir->unmanaged_exclude_files++; /* see validate_untracked_cache() */
	add_excludes_from_file_1(dir, fname, NULL);
}

int match_basename(const char *basename, int basenamelen,
		   const char *pattern, int prefix, int patternlen,
		   int flags)
{
	if (prefix == patternlen) {
		if (patternlen == basenamelen &&
