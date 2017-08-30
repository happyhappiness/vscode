{
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
			return (ARCHIVE_FAILED);
		}
		r = fstatvfs(fd, &sfs);
		if (r == 0)
			xr = get_xfer_size(t, fd, NULL);
		close(fd);
#else
		r = statvfs(tree_current_access_path(t), &sfs);
		if (r == 0)
			xr = get_xfer_size(t, -1, tree_current_access_path(t));
#endif
	}