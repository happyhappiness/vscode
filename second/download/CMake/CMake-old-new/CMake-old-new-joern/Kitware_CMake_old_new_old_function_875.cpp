static int
setup_current_filesystem(struct archive_read_disk *a)
{
	struct tree *t = a->tree;
	struct statvfs sfs;
	int r, xr = 0;

	t->current_filesystem->synthetic = -1;
	if (tree_current_is_symblic_link_target(t)) {
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
	if (r == -1 || xr == -1) {
		t->current_filesystem->remote = -1;
		archive_set_error(&a->archive, errno, "statvfs failed");
		return (ARCHIVE_FAILED);
	} else if (xr == 1) {
		/* Usuall come here unless NetBSD supports _PC_REC_XFER_ALIGN
		 * for pathconf() function. */
		t->current_filesystem->xfer_align = sfs.f_frsize;
		t->current_filesystem->max_xfer_size = -1;
		t->current_filesystem->min_xfer_size = sfs.f_iosize;
		t->current_filesystem->incr_xfer_size = sfs.f_iosize;
	}
	if (sfs.f_flag & ST_LOCAL)
		t->current_filesystem->remote = 0;
	else
		t->current_filesystem->remote = 1;

	if (sfs.f_flag & ST_NOATIME)
		t->current_filesystem->noatime = 1;
	else
		t->current_filesystem->noatime = 0;

	/* Set maximum filename length. */
	t->current_filesystem->name_max = sfs.f_namemax;
	return (ARCHIVE_OK);
}