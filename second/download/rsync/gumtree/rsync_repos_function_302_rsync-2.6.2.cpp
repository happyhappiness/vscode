static int check_exclude_file(char *fname, int is_dir, int exclude_level)
{
	int rc;

#if 0 /* This currently never happens, so avoid a useless compare. */
	if (exclude_level == NO_EXCLUDES)
		return 0;
#endif
	if (fname) {
		/* never exclude '.', even if somebody does --exclude '*' */
		if (fname[0] == '.' && !fname[1])
			return 0;
		/* Handle the -R version of the '.' dir. */
		if (fname[0] == '/') {
			int len = strlen(fname);
			if (fname[len-1] == '.' && fname[len-2] == '/')
				return 0;
		}
	}
	if (server_exclude_list.head
	    && check_exclude(&server_exclude_list, fname, is_dir) < 0)
		return 1;
	if (exclude_level != ALL_EXCLUDES)
		return 0;
	if (exclude_list.head
	    && (rc = check_exclude(&exclude_list, fname, is_dir)) != 0)
		return rc < 0;
	if (local_exclude_list.head
	    && check_exclude(&local_exclude_list, fname, is_dir) < 0)
		return 1;
	return 0;
}