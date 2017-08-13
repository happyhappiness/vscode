static ssize_t
lzop_filter_read(struct archive_read_filter *self, const void **p)
{
	struct read_lzop *state = (struct read_lzop *)self->data;
	const void *b;
	lzo_uint out_size;
	uint32_t cksum;
	int ret, r;

	if (state->unconsumed_bytes) {
		__archive_read_filter_consume(self->upstream,
		    state->unconsumed_bytes);
		state->unconsumed_bytes = 0;
	}
	if (state->eof)
		return (0);

	for (;;) {
		if (!state->in_stream) {
			ret = consume_header(self);
			if (ret < ARCHIVE_OK)
				return (ret);
			if (ret == ARCHIVE_EOF) {
				state->eof = 1;
				return (0);
			}
		}
		ret = consume_block_info(self);
		if (ret < ARCHIVE_OK)
			return (ret);
		if (ret == ARCHIVE_EOF)
			state->in_stream = 0;
		else
			break;
	}

	if (state->out_block == NULL ||
	    state->out_block_size < state->uncompressed_size) {
		void *new_block;

		new_block = realloc(state->out_block, state->uncompressed_size);
		if (new_block == NULL) {
			archive_set_error(&self->archive->archive, ENOMEM,
			    "Can't allocate data for lzop decompression");
			return (ARCHIVE_FATAL);
		}
		state->out_block = new_block;
		state->out_block_size = state->uncompressed_size;
	}

	b = __archive_read_filter_ahead(self->upstream,
		state->compressed_size, NULL);
	if (b == NULL) {
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT, "Truncated lzop data");
		return (ARCHIVE_FATAL);
	}
	if (state->flags & CRC32_COMPRESSED)
		cksum = crc32(crc32(0, NULL, 0), b, state->compressed_size);
	else if (state->flags & ADLER32_COMPRESSED)
		cksum = adler32(adler32(0, NULL, 0), b, state->compressed_size);
	else
		cksum = state->compressed_cksum;
	if (cksum != state->compressed_cksum) {
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC, "Corrupted data");
		return (ARCHIVE_FATAL);
	}

	/*
	 * If the both uncompressed size and compressed size are the same,
	 * we do not decompress this block.
	 */
	if (state->uncompressed_size == state->compressed_size) {
		*p = b;
		state->total_out += state->compressed_size;
		state->unconsumed_bytes = state->compressed_size;
		return ((ssize_t)state->uncompressed_size);
	}

	/*
	 * Drive lzo uncompression.
	 */
	out_size = (lzo_uint)state->uncompressed_size;
	r = lzo1x_decompress_safe(b, (lzo_uint)state->compressed_size,
		state->out_block, &out_size, NULL);
	switch (r) {
	case LZO_E_OK:
		if (out_size == state->uncompressed_size)
			break;
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC, "Corrupted data");
		return (ARCHIVE_FATAL);
	case LZO_E_OUT_OF_MEMORY:
		archive_set_error(&self->archive->archive, ENOMEM,
		    "lzop decompression failed: out of memory");
		return (ARCHIVE_FATAL);
	default:
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "lzop decompression failed: %d", r);
		return (ARCHIVE_FATAL);
	}

	if (state->flags & CRC32_UNCOMPRESSED)
		cksum = crc32(crc32(0, NULL, 0), state->out_block,
		    state->uncompressed_size);
	else if (state->flags & ADLER32_UNCOMPRESSED)
		cksum = adler32(adler32(0, NULL, 0), state->out_block,
		    state->uncompressed_size);
	else
		cksum = state->uncompressed_cksum;
	if (cksum != state->uncompressed_cksum) {
		archive_set_error(&self->archive->archive,
		    ARCHIVE_ERRNO_MISC, "Corrupted data");
		return (ARCHIVE_FATAL);
	}

	__archive_read_filter_consume(self->upstream, state->compressed_size);
	*p = state->out_block;
	state->total_out += out_size;
	return ((ssize_t)out_size);
}