				 * NULL pointer to strlen().  */
	switch (key[0]) {
	case 'G':
		/* Reject GNU.sparse.* headers on non-regular files. */
		if (strncmp(key, "GNU.sparse", 10) == 0 &&
		    !tar->sparse_allowed) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Non-regular file cannot be sparse");
			return (ARCHIVE_FATAL);
		}

		/* GNU "0.0" sparse pax format. */
		if (strcmp(key, "GNU.sparse.numblocks") == 0) {
			tar->sparse_offset = -1;
