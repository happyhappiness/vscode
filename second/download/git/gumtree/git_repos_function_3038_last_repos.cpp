static void init_socket_directory(const char *path)
{
	struct stat st;
	char *path_copy = xstrdup(path);
	char *dir = dirname(path_copy);

	if (!stat(dir, &st)) {
		if (st.st_mode & 077)
			die(_(permissions_advice), dir);
	} else {
		/*
		 * We must be sure to create the directory with the correct mode,
		 * not just chmod it after the fact; otherwise, there is a race
		 * condition in which somebody can chdir to it, sleep, then try to open
		 * our protected socket.
		 */
		if (safe_create_leading_directories_const(dir) < 0)
			die_errno("unable to create directories for '%s'", dir);
		if (mkdir(dir, 0700) < 0)
			die_errno("unable to mkdir '%s'", dir);
	}

	if (chdir(dir))
		/*
		 * We don't actually care what our cwd is; we chdir here just to
		 * be a friendly daemon and avoid tying up our original cwd.
		 * If this fails, it's OK to just continue without that benefit.
		 */
		;

	free(path_copy);
}