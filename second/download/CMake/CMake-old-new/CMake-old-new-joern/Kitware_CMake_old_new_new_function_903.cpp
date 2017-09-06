static int
setup_current_filesystem(struct archive_read_disk *a)
{
	struct tree *t = a->tree;
	struct statfs sfs;
#if defined(HAVE_GETVFSBYNAME) && defined(VFCF_SYNTHETIC)
	struct xvfsconf vfc;
#endif
	int r, xr = 0;
#if !defined(HAVE_STRUCT_STATFS_F_NAMEMAX)
	long nm;
#endif

	t->current_filesystem->synthetic = -1;
	t->current_filesystem->remote = -1;
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
		r = fstatfs(fd, &sfs);
		if (r == 0)
			xr = get_xfer_size(t, fd, NULL);
		close(fd);
#else
		if (tree_enter_working_dir(t) != 0) {
			archive_set_error(&a->archive, errno, "fchdir failed");
			return (ARCHIVE_FAILED);
		}
		r = statfs(tree_current_access_path(t), &sfs);
		if (r == 0)
			xr = get_xfer_size(t, -1, tree_current_access_path(t));
#endif
	} else {
		r = fstatfs(tree_current_dir_fd(t), &sfs);
		if (r == 0)
			xr = get_xfer_size(t, tree_current_dir_fd(t), NULL);
	}
	if (r == -1 || xr == -1) {
		archive_set_error(&a->archive, errno, "statfs failed");
		return (ARCHIVE_FAILED);
	} else if (xr == 1) {
		/* pathconf(_PC_REX_*) operations are not supported. */
		t->current_filesystem->xfer_align = sfs.f_bsize;
		t->current_filesystem->max_xfer_size = -1;
		t->current_filesystem->min_xfer_size = sfs.f_iosize;
		t->current_filesystem->incr_xfer_size = sfs.f_iosize;
	}
	if (sfs.f_flags & MNT_LOCAL)
		t->current_filesystem->remote = 0;
	else
		t->current_filesystem->remote = 1;

#if defined(HAVE_GETVFSBYNAME) && defined(VFCF_SYNTHETIC)
	r = getvfsbyname(sfs.f_fstypename, &vfc);
	if (r == -1) {
		archive_set_error(&a->archive, errno, "getvfsbyname failed");
		return (ARCHIVE_FAILED);
	}
	if (vfc.vfc_flags & VFCF_SYNTHETIC)
		t->current_filesystem->synthetic = 1;
	else
		t->current_filesystem->synthetic = 0;
#endif

#if defined(MNT_NOATIME)
	if (sfs.f_flags & MNT_NOATIME)
		t->current_filesystem->noatime = 1;
	else
#endif
		t->current_filesystem->noatime = 0;

#if defined(HAVE_READDIR_R)
	/* Set maximum filename length. */
#if defined(HAVE_STRUCT_STATFS_F_NAMEMAX)
	t->current_filesystem->name_max = sfs.f_namemax;
#else
	/* Mac OS X does not have f_namemax in struct statfs. */
	if (tree_current_is_symblic_link_target(t)) {
		if (tree_enter_working_dir(t) != 0) {
			archive_set_error(&a->archive, errno, "fchdir failed");
			return (ARCHIVE_FAILED);
		}
		nm = pathconf(tree_current_access_path(t), _PC_NAME_MAX);
	} else
		nm = fpathconf(tree_current_dir_fd(t), _PC_NAME_MAX);
	if (nm == -1)
		t->current_filesystem->name_max = NAME_MAX;
	else
		t->current_filesystem->name_max = nm;
#endif
#endif /* HAVE_READDIR_R */
	return (ARCHIVE_OK);
}