static ssize_t
lz4_filter_read_default_stream(struct archive_read_filter *self, const void **p)
{
	struct private_data *state = (struct private_data *)self->data;
	const char *read_buf;
	ssize_t bytes_remaining;
	ssize_t ret;

	if (state->stage == SELECT_STREAM) {
		state->stage = READ_DEFAULT_STREAM;
		/* First, read a descriptor. */
		if((ret = lz4_filter_read_descriptor(self)) != ARCHIVE_OK)
			return (ret);
		state->stage = READ_DEFAULT_BLOCK;
	}
	/* Decompress a block. */
	ret = lz4_filter_read_data_block(self, p);

	/* If the end of block is detected, change the filter status
	   to read next stream. */
	if (ret == 0 && *p == NULL)
		state->stage = SELECT_STREAM;

	/* Optional process, checking a stream sum. */
	if (state->flags.stream_checksum) {
		if (state->stage == SELECT_STREAM) {
			unsigned int checksum;
			unsigned int checksum_stream;
			read_buf = __archive_read_filter_ahead(self->upstream,
			    4, &bytes_remaining);
			if (read_buf == NULL) {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC, "truncated lz4 input");
				return (ARCHIVE_FATAL);
			}
			checksum = archive_le32dec(read_buf);
			__archive_read_filter_consume(self->upstream, 4);
			checksum_stream = __archive_xxhash.XXH32_digest(
			    state->xxh32_state);
			state->xxh32_state = NULL;
			if (checksum != checksum_stream) {
				archive_set_error(&self->archive->archive,
				    ARCHIVE_ERRNO_MISC,
				    "lz4 stream cheksum error");
				return (ARCHIVE_FATAL);
			}
		} else if (ret > 0)
			__archive_xxhash.XXH32_update(state->xxh32_state,
			    *p, (int)ret);
	}
	return (ret);
}