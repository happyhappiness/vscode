		r = fstatfs(tree_current_dir_fd(t), &sfs);
		if (r == 0)
			xr = get_xfer_size(t, tree_current_dir_fd(t), NULL);
#elif defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_FDOPENDIR)
#error "Unexpected case. Please tell us about this error."
#else
		vr = statvfs(".", &svfs);
		r = statfs(".", &sfs);
		if (r == 0)
