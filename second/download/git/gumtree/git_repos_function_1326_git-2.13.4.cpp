static int create_one_file(struct apply_state *state,
			   char *path,
			   unsigned mode,
			   const char *buf,
			   unsigned long size)
{
	int res;

	if (state->cached)
		return 0;

	res = try_create_file(path, mode, buf, size);
	if (res < 0)
		return -1;
	if (!res)
		return 0;

	if (errno == ENOENT) {
		if (safe_create_leading_directories(path))
			return 0;
		res = try_create_file(path, mode, buf, size);
		if (res < 0)
			return -1;
		if (!res)
			return 0;
	}

	if (errno == EEXIST || errno == EACCES) {
		/* We may be trying to create a file where a directory
		 * used to be.
		 */
		struct stat st;
		if (!lstat(path, &st) && (!S_ISDIR(st.st_mode) || !rmdir(path)))
			errno = EEXIST;
	}

	if (errno == EEXIST) {
		unsigned int nr = getpid();

		for (;;) {
			char newpath[PATH_MAX];
			mksnpath(newpath, sizeof(newpath), "%s~%u", path, nr);
			res = try_create_file(newpath, mode, buf, size);
			if (res < 0)
				return -1;
			if (!res) {
				if (!rename(newpath, path))
					return 0;
				unlink_or_warn(newpath);
				break;
			}
			if (errno != EEXIST)
				break;
			++nr;
		}
	}
	return error_errno(_("unable to write file '%s' mode %o"),
			   path, mode);
}