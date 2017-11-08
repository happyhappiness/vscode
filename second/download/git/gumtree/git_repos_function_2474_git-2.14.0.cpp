struct exclude *last_exclude_matching(struct dir_struct *dir,
				      struct index_state *istate,
				      const char *pathname,
				      int *dtype_p)
{
	int pathlen = strlen(pathname);
	const char *basename = strrchr(pathname, '/');
	basename = (basename) ? basename+1 : pathname;

	prep_exclude(dir, istate, pathname, basename-pathname);

	if (dir->exclude)
		return dir->exclude;

	return last_exclude_matching_from_lists(dir, istate, pathname, pathlen,
			basename, dtype_p);
}