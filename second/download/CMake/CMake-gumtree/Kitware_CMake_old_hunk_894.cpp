			xr = get_xfer_size(t, fd, NULL);
		close(fd);
#else
		r = statfs(tree_current_access_path(t), &sfs);
		if (r == 0)
			xr = get_xfer_size(t, -1, tree_current_access_path(t));
