{
	struct read_fd_data *mine = (struct read_fd_data *)client_data;
	int64_t skip = request;
	int64_t old_offset, new_offset;
	int skip_bits = sizeof(skip) * 8 - 1;  /* off_t is a signed type. */

	if (!mine->use_lseek)
		return (0);

	/* Reduce a request that would overflow the 'skip' variable. */
	if (sizeof(request) > sizeof(skip)) {
		int64_t max_skip =
		    (((int64_t)1 << (skip_bits - 1)) - 1) * 2 + 1;
		if (request > max_skip)
			skip = max_skip;
	}

	/* Reduce request to the next smallest multiple of block_size */
	request = (request / mine->block_size) * mine->block_size;
	if (request == 0)
		return (0);

	if (((old_offset = lseek(mine->fd, 0, SEEK_CUR)) >= 0) &&
	    ((new_offset = lseek(mine->fd, skip, SEEK_CUR)) >= 0))
		return (new_offset - old_offset);

	/* If seek failed once, it will probably fail again. */
	mine->use_lseek = 0;

	/* Let libarchive recover with read+discard. */
	if (errno == ESPIPE)
		return (0);

	/*
	 * There's been an error other than ESPIPE. This is most
	 * likely caused by a programmer error (too large request)
	 * or a corrupted archive file.
	 */
	archive_set_error(a, errno, "Error seeking");
	return (-1);
}