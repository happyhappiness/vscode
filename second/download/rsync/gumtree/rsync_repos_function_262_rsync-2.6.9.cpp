int push_dir(char *dir, int set_path_only)
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

	if ((*dir == '/' ? len : curr_dir_len + 1 + len) >= sizeof curr_dir)
		return 0;

	if (!set_path_only && chdir(dir))
		return 0;

	if (*dir == '/') {
		memcpy(curr_dir, dir, len + 1);
		curr_dir_len = len;
	} else {
		curr_dir[curr_dir_len++] = '/';
		memcpy(curr_dir + curr_dir_len, dir, len + 1);
		curr_dir_len += len;
	}

	curr_dir_len = clean_fname(curr_dir, 1);
	if (sanitize_paths) {
		if (module_dirlen > curr_dir_len)
			module_dirlen = curr_dir_len;
		curr_dir_depth = count_dir_elements(curr_dir + module_dirlen);
	}

	return 1;
}