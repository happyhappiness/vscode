{
		t->current_filesystem->incr_xfer_size =
		    fpathconf(fd, _PC_REC_INCR_XFER_SIZE);
		t->current_filesystem->max_xfer_size =
		    fpathconf(fd, _PC_REC_MAX_XFER_SIZE);
		t->current_filesystem->min_xfer_size =
		    fpathconf(fd, _PC_REC_MIN_XFER_SIZE);
		t->current_filesystem->xfer_align =
		    fpathconf(fd, _PC_REC_XFER_ALIGN);
	}