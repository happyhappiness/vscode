int handle_partial_dir(const char *fname, int create)
{
	char *fn, *dir;

	if (fname != partial_fname)
		return 1;
	if (!create && *partial_dir == '/')
		return 1;
	if (!(fn = strrchr(partial_fname, '/')))
		return 1;

	*fn = '\0';
	dir = partial_fname;
	if (create) {
		STRUCT_STAT st;
		int statret = do_lstat(dir, &st);
		if (statret == 0 && !S_ISDIR(st.st_mode)) {
			if (do_unlink(dir) < 0) {
				*fn = '/';
				return 0;
			}
			statret = -1;
		}
		if (statret < 0 && do_mkdir(dir, 0700) < 0) {
			*fn = '/';
			return 0;
		}
	} else
		do_rmdir(dir);
	*fn = '/';

	return 1;
}