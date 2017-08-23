static ssize_t
gzip_filter_read(struct archive_read_filter *self, const void **p)
{
	struct private_data *state;
	size_t decompressed;
	ssize_t avail_in;
	int ret;

	state = (struct private_data *)self->data;

	/* Empty our output buffer. */
	state->stream.next_out = state->out_block;
	state->stream.avail_out = (uInt)state->out_block_size;

	/* Try to fill the output buffer. */
	while (state->stream.avail_out > 0 && !state->eof) {
		/* If we're not in a stream, read a header
		 * and initialize the decompression library. */
		if (!state->in_stream) {
			ret = consume_header(self);
			if (ret == ARCHIVE_EOF) {
				state->eof = 1;
				break;
			}
			if (ret < ARCHIVE_OK)
				return (ret);
		}

		/* Peek at the next available data. */
		/* ZLib treats stream.next_in as const but doesn't declare
		 * it so, hence this ugly cast. */
		state->stream.next_in = (unsigned char *)(uintptr_t)
		    __archive_read_filter_ahead(self->upstream, 1, &avail_in);
		if (state->stream.next_in == NULL) {
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "truncated gzip input");
			return (ARCHIVE_FATAL);
		}
		state->stream.avail_in = (uInt)avail_in;

		/* Decompress and consume some of that data. */
		ret = inflate(&(state->stream), 0);
		switch (ret) {
		case Z_OK: /* Decompressor made some progress. */
			__archive_read_filter_consume(self->upstream,
			    avail_in - state->stream.avail_in);
			break;
		case Z_STREAM_END: /* Found end of stream. */
			__archive_read_filter_consume(self->upstream,
			    avail_in - state->stream.avail_in);
			/* Consume the stream trailer; release the
			 * decompression library. */
			ret = consume_trailer(self);
			if (ret < ARCHIVE_OK)
				return (ret);
			break;
		default:
			/* Return an error. */
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "gzip decompression failed");
			return (ARCHIVE_FATAL);
		}
	}

	/* We've read as much as we can. */
	decompressed = state->stream.next_out - state->out_block;
	state->total_out += decompressed;
	if (decompressed == 0)
		*p = NULL;
	else
		*p = state->out_block;
	return (decompressed);
}