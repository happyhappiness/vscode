	/* Make sure we have a whole block. */
	read_buf = __archive_read_filter_ahead(self->upstream,
	    4 + compressed, NULL);
	if (read_buf == NULL) {
		archive_set_error(&(self->archive->archive),
		    ARCHIVE_ERRNO_MISC, "truncated lz4 input");
		return (ARCHIVE_FATAL);
	}
	ret = LZ4_decompress_safe(read_buf + 4, state->out_block,
	    compressed, (int)state->out_block_size);
	if (ret < 0) {