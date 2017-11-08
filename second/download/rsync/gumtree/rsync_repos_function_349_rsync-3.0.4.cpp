int change_dir(const char *dir, int set_path_only)
{
	static int initialised;
	unsigned int len;

	if (!initialised) {
		initialised = 1;
		getcwd(curr_dir, sizeof curr_dir - 1);
		curr_dir_len = strlen(curr_dir);
	}

	if (!dir)	/* this call was probably just to initialize */
		return 0;

	len = strlen(dir);
	if (len == 1 && *dir == '.')
		return 1;

	if (*dir == '/') {
		if (len >= sizeof curr_dir) {
			errno = ENAMETOOLONG;
			return 0;
		}
		if (!set_path_only && chdir(dir))
			return 0;
		memcpy(curr_dir, dir, len + 1);
	} else {
		if (curr_dir_len + 1 + len >= sizeof curr_dir) {
			errno = ENAMETOOLONG;
			return 0;
		}
		curr_dir[curr_dir_len] = '/';
		memcpy(curr_dir + curr_dir_len + 1, dir, len + 1);

		if (!set_path_only && chdir(curr_dir)) {
			curr_dir[curr_dir_len] = '\0';
			return 0;
		}
	}

	curr_dir_len = clean_fname(curr_dir, CFN_COLLAPSE_DOT_DOT_DIRS);
	if (sanitize_paths) {
		if (module_dirlen > curr_dir_len)
			module_dirlen = curr_dir_len;
		curr_dir_depth = count_dir_elements(curr_dir + module_dirlen);
	}

	if (verbose >= 5 && !set_path_only)
		rprintf(FINFO, "[%s] change_dir(%s)\n", who_am_i(), curr_dir);

	return 1;
}