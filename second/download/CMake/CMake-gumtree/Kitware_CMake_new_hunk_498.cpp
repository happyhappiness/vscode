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

	} else {

#ifdef HAVE_FSTATFS

#if defined(HAVE_FSTATVFS)

		vr = fstatvfs(tree_current_dir_fd(t), &svfs);

#endif

		r = fstatfs(tree_current_dir_fd(t), &sfs);

		if (r == 0)

			xr = get_xfer_size(t, tree_current_dir_fd(t), NULL);

