(entries-- > 0) {
		/* Parse offset/size */
		offset = gnu_sparse_10_atol(a, tar, &remaining, unconsumed);
		if (offset < 0)
			return (ARCHIVE_FATAL);
		size = gnu_sparse_10_atol(a, tar, &remaining, unconsumed);
		if (size < 0)
			return (ARCHIVE_FATAL);
		/* Add a new sparse entry. */
		if (gnu_add_sparse_entry(a, tar, offset, size) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}