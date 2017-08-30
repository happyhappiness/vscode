			xr = get_xfer_size(t, fd, NULL);

		close(fd);

#else

		vr = statvfs(tree_current_access_path(t), &svfs);

		r = statfs(tree_current_access_path(t), &sfs);

		if (r == 0)

