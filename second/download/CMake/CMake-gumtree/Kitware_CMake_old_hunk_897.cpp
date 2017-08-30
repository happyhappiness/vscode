	int r, vr = 0, xr = 0;

	if (tree_current_is_symblic_link_target(t)) {
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR)
		/*
		 * Get file system statistics on any directory
		 * where current is.
		 */
		int fd = openat(tree_current_dir_fd(t),
		    tree_current_access_path(t), O_RDONLY);
		if (fd < 0) {
			archive_set_error(&a->archive, errno,
			    "openat failed");
