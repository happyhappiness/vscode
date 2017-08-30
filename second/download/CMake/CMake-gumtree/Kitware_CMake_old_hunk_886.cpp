	for (;;) {
		int i, r;

		r = ioctl(fd, FS_IOC_FIEMAP, fm); 
		if (r < 0) {
			/* When errno is ENOTTY, it is better we should
			 * return ARCHIVE_OK because an earlier version
			 *(<2.6.28) cannot perfom FS_IOC_FIEMAP.
			 * We should also check if errno is EOPNOTSUPP,
			 * it means "Operation not supported". */
			if (errno != ENOTTY && errno != EOPNOTSUPP) {
				archive_set_error(&a->archive, errno,
				    "FIEMAP failed");
				exit_sts = ARCHIVE_FAILED;
			}
			goto exit_setup_sparse;
		}
		if (fm->fm_mapped_extents == 0)
			break;
		fe = fm->fm_extents;
		for (i = 0; i < fm->fm_mapped_extents; i++, fe++) {
			if (!(fe->fe_flags & FIEMAP_EXTENT_UNWRITTEN)) {
				/* The fe_length of the last block does not
				 * adjust itself to its size files. */
				int64_t length = fe->fe_length;
				if (fe->fe_logical + length > size)
					length -= fe->fe_logical + length - size;
				if (fe->fe_logical == 0 && length == size) {
					/* This is not sparse. */
