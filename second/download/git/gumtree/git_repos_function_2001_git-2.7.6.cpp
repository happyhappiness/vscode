struct exclude *last_exclude_matching(struct dir_struct *dir,
					     const char *pathname,
					     int *dtype_p)
{
	int pathlen = strlen(pathname);
	const char *basename = strrchr(pathname, '/');
	basename = (basename) ? basename+1 : pathname;

	prep_exclude(dir, pathname, basename-pathname);

	if (dir->exclude)
		return dir->exclude;

	return last_exclude_matching_from_lists(dir, pathname, pathlen,
			basename, dtype_p);
}