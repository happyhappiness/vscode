static int check_exclude_file(char *fname, int is_dir, int exclude_level)
{
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
	if (server_exclude_list
	 && check_exclude(server_exclude_list, fname, is_dir))
		return 1;
	if (exclude_level != ALL_EXCLUDES)
		return 0;
	if (exclude_list && check_exclude(exclude_list, fname, is_dir))
		return 1;
	if (local_exclude_list
	 && check_exclude(local_exclude_list, fname, is_dir))
		return 1;
	return 0;
}