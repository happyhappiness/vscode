static int
setup_current_filesystem(struct archive_read_disk *a)
{
	struct tree *t = a->tree;
	struct statvfs sfs;
	int r, xr = 0;

	t->current_filesystem->synthetic = -1;/* Not supported */
	t->current_filesystem->remote = -1;/* Not supported */
	if (tree_current_is_symblic_link_target(t)) {
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
		r = fstatvfs(fd, &sfs);
		if (r == 0)
			xr = get_xfer_size(t, fd, NULL);
		close(fd);
#else
		if (tree_enter_working_dir(t) != 0) {
			archive_set_error(&a->archive, errno, "fchdir failed");
			return (ARCHIVE_FAILED);
		}
		r = statvfs(tree_current_access_path(t), &sfs);
		if (r == 0)
			xr = get_xfer_size(t, -1, tree_current_access_path(t));
#endif
	} else {
#ifdef HAVE_FSTATVFS
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
#endif
	}
	if (r == -1 || xr == -1) {
		t->current_filesystem->synthetic = -1;
		t->current_filesystem->remote = -1;
		archive_set_error(&a->archive, errno, "statvfs failed");
		return (ARCHIVE_FAILED);
	} else if (xr == 1) {
		/* pathconf(_PC_REX_*) operations are not supported. */
		t->current_filesystem->xfer_align = sfs.f_frsize;
		t->current_filesystem->max_xfer_size = -1;
		t->current_filesystem->min_xfer_size = sfs.f_bsize;
		t->current_filesystem->incr_xfer_size = sfs.f_bsize;
	}

#if defined(ST_NOATIME)
	if (sfs.f_flag & ST_NOATIME)
		t->current_filesystem->noatime = 1;
	else
#endif
		t->current_filesystem->noatime = 0;

#if defined(HAVE_READDIR_R)
	/* Set maximum filename length. */
	t->current_filesystem->name_max = sfs.f_namemax;
#endif
	return (ARCHIVE_OK);
}