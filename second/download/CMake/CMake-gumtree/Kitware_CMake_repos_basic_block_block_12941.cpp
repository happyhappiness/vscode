{
	ssize_t bytes_read;
	int entries;
	int64_t offset, size, to_skip, remaining;

	/* Clear out the existing sparse list. */
	gnu_clear_sparse_list(tar);

	remaining = tar->entry_bytes_remaining;

	/* Parse entries. */
	entries = (int)gnu_sparse_10_atol(a, tar, &remaining, unconsumed);
	if (entries < 0)
		return (ARCHIVE_FATAL);
	/* Parse the individual entries. */
	while (entries-- > 0) {
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
	/* Skip rest of block... */
	tar_flush_unconsumed(a, unconsumed);
	bytes_read = (ssize_t)(tar->entry_bytes_remaining - remaining);
	to_skip = 0x1ff & -bytes_read;
	/* Fail if tar->entry_bytes_remaing would get negative */
	if (to_skip > remaining)
		return (ARCHIVE_FATAL);
	if (to_skip != __archive_read_consume(a, to_skip))
		return (ARCHIVE_FATAL);
	return ((ssize_t)(bytes_read + to_skip));
}