			xr = get_xfer_size(t, fd, NULL);

		close(fd);

#else

		if (tree_enter_working_dir(t) != 0) {

			archive_set_error(&a->archive, errno, "fchdir failed");

			return (ARCHIVE_FAILED);

		}

		vr = statvfs(tree_current_access_path(t), &svfs);

		r = statfs(tree_current_access_path(t), &sfs);

		if (r == 0)

