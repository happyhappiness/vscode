		r = fstatvfs(tree_current_dir_fd(t), &sfs);
		if (r == 0)
			xr = get_xfer_size(t, tree_current_dir_fd(t), NULL);
#else
		if (tree_enter_working_dir(t) != 0) {
			archive_set_error(&a->archive, errno, "fchdir failed");
			return (ARCHIVE_FAILED);
		}
		r = statvfs(".", &sfs);
		if (r == 0)
			xr = get_xfer_size(t, -1, ".");
