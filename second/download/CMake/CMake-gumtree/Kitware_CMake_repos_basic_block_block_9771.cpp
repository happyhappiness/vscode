{
#if defined(HAVE_OPENAT)
		/*
		 * Get file system statistics on any directory
		 * where current is.
		 */
		int fd = openat(tree_current_dir_fd(t),
		    tree_current_access_path(t), O_RDONLY | O_CLOEXEC);
		__archive_ensure_cloexec_flag(fd);
		if (fd < 0) {
			archive_set_error(&a->archive, errno,
			    "openat failed");
			return (ARCHIVE_FAILED);
		}
#if defined(HAVE_FSTATVFS)
		vr = fstatvfs(fd, &svfs);/* for f_flag, mount flags */
#endif
		r = fstatfs(fd, &sfs);
		if (r == 0)
			xr = get_xfer_size(t, fd, NULL);
		close(fd);
#else
		if (tree_enter_working_dir(t) != 0) {
			archive_set_error(&a->archive, errno, "fchdir failed");
			return (ARCHIVE_FAILED);
		}
#if defined(HAVE_STATVFS)
		vr = statvfs(tree_current_access_path(t), &svfs);
#endif
		r = statfs(tree_current_access_path(t), &sfs);
		if (r == 0)
			xr = get_xfer_size(t, -1, tree_current_access_path(t));
#endif
	}