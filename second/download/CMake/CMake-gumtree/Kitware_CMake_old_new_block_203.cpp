{
	struct private_data *state = (struct private_data *)self->data;
	int compressed;
	const char *read_buf;
	ssize_t ret;

	*p = NULL;
	ret = lz4_allocate_out_block_for_legacy(self);
	if (ret != ARCHIVE_OK)
		return ret;

	/* Make sure we have 4 bytes for a block size. */
	read_buf = __archive_read_filter_ahead(self->upstream, 4, NULL);
	if (read_buf == NULL) {
		if (state->stage == SELECT_STREAM) {
			state->stage = READ_LEGACY_STREAM;
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "truncated lz4 input");
			return (ARCHIVE_FATAL);
		}
		state->stage = SELECT_STREAM;
		return 0;
	}
	state->stage = READ_LEGACY_BLOCK;
	compressed = archive_le32dec(read_buf);
	if (compressed > LZ4_COMPRESSBOUND(LEGACY_BLOCK_SIZE)) {
		state->stage = SELECT_STREAM;
		return 0;
	}

	/* Make sure we have a whole block. */
	read_buf = __archive_read_filter_ahead(self->upstream,
	    4 + compressed, NULL);
	ret = LZ4_decompress_safe(read_buf + 4, state->out_block,
	    compressed, (int)state->out_block_size);
	if (ret < 0) {
		archive_set_error(&(self->archive->archive),
		    ARCHIVE_ERRNO_MISC, "lz4 decompression failed");
		return (ARCHIVE_FATAL);
	}
	*p = state->out_block;
	state->unconsumed = 4 + compressed;
	return ret;
}