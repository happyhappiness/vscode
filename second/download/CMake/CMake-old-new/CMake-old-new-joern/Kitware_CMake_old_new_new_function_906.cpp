static int
setup_current_filesystem(struct archive_read_disk *a)
{
	struct tree *t = a->tree;
	struct statfs sfs;
	struct statvfs svfs;
	int r, vr = 0, xr = 0;

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
		vr = fstatvfs(fd, &svfs);/* for f_flag, mount flags */
		r = fstatfs(fd, &sfs);
		if (r == 0)
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
			xr = get_xfer_size(t, -1, tree_current_access_path(t));
#endif
	} else {
#ifdef HAVE_FSTATFS
		vr = fstatvfs(tree_current_dir_fd(t), &svfs);
		r = fstatfs(tree_current_dir_fd(t), &sfs);
		if (r == 0)
			xr = get_xfer_size(t, tree_current_dir_fd(t), NULL);
#else
		if (tree_enter_working_dir(t) != 0) {
			archive_set_error(&a->archive, errno, "fchdir failed");
			return (ARCHIVE_FAILED);
		}
		vr = statvfs(".", &svfs);
		r = statfs(".", &sfs);
		if (r == 0)
			xr = get_xfer_size(t, -1, ".");
#endif
	}
	if (r == -1 || xr == -1 || vr == -1) {
		t->current_filesystem->synthetic = -1;
		t->current_filesystem->remote = -1;
		archive_set_error(&a->archive, errno, "statfs failed");
		return (ARCHIVE_FAILED);
	} else if (xr == 1) {
		/* pathconf(_PC_REX_*) operations are not supported. */
		t->current_filesystem->xfer_align = svfs.f_frsize;
		t->current_filesystem->max_xfer_size = -1;
		t->current_filesystem->min_xfer_size = svfs.f_bsize;
		t->current_filesystem->incr_xfer_size = svfs.f_bsize;
	}
	switch (sfs.f_type) {
	case AFS_SUPER_MAGIC:
	case CIFS_SUPER_MAGIC:
	case CODA_SUPER_MAGIC:
	case NCP_SUPER_MAGIC:/* NetWare */
	case NFS_SUPER_MAGIC:
	case SMB_SUPER_MAGIC:
		t->current_filesystem->remote = 1;
		t->current_filesystem->synthetic = 0;
		break;
	case DEVFS_SUPER_MAGIC:
	case PROC_SUPER_MAGIC:
	case USBDEVICE_SUPER_MAGIC:
		t->current_filesystem->remote = 0;
		t->current_filesystem->synthetic = 1;
		break;
	default:
		t->current_filesystem->remote = 0;
		t->current_filesystem->synthetic = 0;
		break;
	}

#if defined(ST_NOATIME)
	if (svfs.f_flag & ST_NOATIME)
		t->current_filesystem->noatime = 1;
	else
#endif
		t->current_filesystem->noatime = 0;

#if defined(HAVE_READDIR_R)
	/* Set maximum filename length. */
	t->current_filesystem->name_max = sfs.f_namelen;
#endif
	return (ARCHIVE_OK);
}