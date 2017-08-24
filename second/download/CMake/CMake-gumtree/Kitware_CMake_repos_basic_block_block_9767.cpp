{
		/* pathconf(_PC_REX_*) operations are not supported. */
#if defined(HAVE_STATVFS)
		t->current_filesystem->xfer_align = svfs.f_frsize;
		t->current_filesystem->max_xfer_size = -1;
		t->current_filesystem->min_xfer_size = svfs.f_bsize;
		t->current_filesystem->incr_xfer_size = svfs.f_bsize;
#else
		t->current_filesystem->xfer_align = sfs.f_frsize;
		t->current_filesystem->max_xfer_size = -1;
		t->current_filesystem->min_xfer_size = sfs.f_bsize;
		t->current_filesystem->incr_xfer_size = sfs.f_bsize;
#endif
	}