static ssize_t
xz_filter_read(struct archive_read_filter *self, const void **p)
{
	struct private_data *state;
	size_t decompressed;
	ssize_t avail_in;
	int ret;

	state = (struct private_data *)self->data;

	/* Empty our output buffer. */
	state->stream.next_out = state->out_block;
	state->stream.avail_out = state->out_block_size;

	/* Try to fill the output buffer. */
	while (state->stream.avail_out > 0 && !state->eof) {
		if (!state->in_stream) {
			/*
			 * Initialize liblzma for lzip
			 */
			ret = lzip_init(self);
			if (ret != ARCHIVE_OK)
				return (ret);
			state->in_stream = 1;
		}
		state->stream.next_in =
		    __archive_read_filter_ahead(self->upstream, 1, &avail_in);
		if (state->stream.next_in == NULL && avail_in < 0) {
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "truncated input");
			return (ARCHIVE_FATAL);
		}
		state->stream.avail_in = avail_in;

		/* Decompress as much as we can in one pass. */
		ret = lzma_code(&(state->stream),
		    (state->stream.avail_in == 0)? LZMA_FINISH: LZMA_RUN);
		switch (ret) {
		case LZMA_STREAM_END: /* Found end of stream. */
			state->eof = 1;
			/* FALL THROUGH */
		case LZMA_OK: /* Decompressor made some progress. */
			__archive_read_filter_consume(self->upstream,
			    avail_in - state->stream.avail_in);
			state->member_in +=
			    avail_in - state->stream.avail_in;
			break;
		default:
			set_error(self, ret);
			return (ARCHIVE_FATAL);
		}
	}

	decompressed = state->stream.next_out - state->out_block;
	state->total_out += decompressed;
	state->member_out += decompressed;
	if (decompressed == 0)
		*p = NULL;
	else {
		*p = state->out_block;
		if (self->code == ARCHIVE_FILTER_LZIP) {
			state->crc32 = lzma_crc32(state->out_block,
			    decompressed, state->crc32);
			if (state->eof) {
				ret = lzip_tail(self);
				if (ret != ARCHIVE_OK)
					return (ret);
			}
		}
	}
	return (decompressed);
}