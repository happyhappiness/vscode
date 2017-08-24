(a->flags & ARCHIVE_EXTRACT_SPARSE) {
		/* XXX TODO XXX Is there a more appropriate choice here ? */
		/* This needn't match the filesystem allocation size. */
		block_size = 16*1024;
	}