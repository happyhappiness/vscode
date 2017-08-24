(r == -1 || xr == -1) {
		t->current_filesystem->remote = -1;
		archive_set_error(&a->archive, errno, "statvfs failed");
		return (ARCHIVE_FAILED);
	} else if (xr == 1) {
		/* Usually come here unless NetBSD supports _PC_REC_XFER_ALIGN
		 * for pathconf() function. */
		t->current_filesystem->xfer_align = sfs.f_frsize;
		t->current_filesystem->max_xfer_size = -1;
#if defined(HAVE_STRUCT_STATVFS_F_IOSIZE)
		t->current_filesystem->min_xfer_size = sfs.f_iosize;
		t->current_filesystem->incr_xfer_size = sfs.f_iosize;
#else
		t->current_filesystem->min_xfer_size = sfs.f_bsize;
		t->current_filesystem->incr_xfer_size = sfs.f_bsize;
#endif
	}