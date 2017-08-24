{
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