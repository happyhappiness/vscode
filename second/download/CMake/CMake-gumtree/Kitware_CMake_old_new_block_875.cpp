(tree_current_is_symblic_link_target(t)) {
		r = statvfs(tree_current_access_path(t), &sfs);
		if (r == 0)
			xr = get_xfer_size(t, -1, tree_current_access_path(t));
	} else {
#ifdef HAVE_FSTATVFS
		r = fstatvfs(tree_current_dir_fd(t), &sfs);
		if (r == 0)
			xr = get_xfer_size(t, tree_current_dir_fd(t), NULL);
#else
		r = statvfs(".", &sfs);
		if (r == 0)
			xr = get_xfer_size(t, -1, ".");
#endif
	}