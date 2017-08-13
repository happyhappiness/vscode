static ssize_t
bzip2_filter_read(struct archive_read_filter *self, const void **p)
{
	struct private_data *state;
	size_t decompressed;
	const char *read_buf;
	ssize_t ret;

	state = (struct private_data *)self->data;

	if (state->eof) {
		*p = NULL;
		return (0);
	}

	/* Empty our output buffer. */
	state->stream.next_out = state->out_block;
	state->stream.avail_out = state->out_block_size;

	/* Try to fill the output buffer. */
	for (;;) {
		if (!state->valid) {
			if (bzip2_reader_bid(self->bidder, self->upstream) == 0) {
				state->eof = 1;
				*p = state->out_block;
				decompressed = state->stream.next_out
				    - state->out_block;
				return (decompressed);
			}
			/* Initialize compression library. */
			ret = BZ2_bzDecompressInit(&(state->stream),
					   0 /* library verbosity */,
					   0 /* don't use low-mem algorithm */);

			/* If init fails, try low-memory algorithm instead. */
			if (ret == BZ_MEM_ERROR)
				ret = BZ2_bzDecompressInit(&(state->stream),
					   0 /* library verbosity */,
					   1 /* do use low-mem algo */);

			if (ret != BZ_OK) {
				const char *detail = NULL;
				int err = ARCHIVE_ERRNO_MISC;
				switch (ret) {
				case BZ_PARAM_ERROR:
					detail = "invalid setup parameter";
					break;
				case BZ_MEM_ERROR:
					err = ENOMEM;
					detail = "out of memory";
					break;
				case BZ_CONFIG_ERROR:
					detail = "mis-compiled library";
					break;
				}
				archive_set_error(&self->archive->archive, err,
				    "Internal error initializing decompressor%s%s",
				    detail == NULL ? "" : ": ",
				    detail);
				return (ARCHIVE_FATAL);
			}
			state->valid = 1;
		}

		/* stream.next_in is really const, but bzlib
		 * doesn't declare it so. <sigh> */
		read_buf =
		    __archive_read_filter_ahead(self->upstream, 1, &ret);
		if (read_buf == NULL) {
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC,
			    "truncated bzip2 input");
			return (ARCHIVE_FATAL);
		}
		state->stream.next_in = (char *)(uintptr_t)read_buf;
		state->stream.avail_in = ret;
		/* There is no more data, return whatever we have. */
		if (ret == 0) {
			state->eof = 1;
			*p = state->out_block;
			decompressed = state->stream.next_out
			    - state->out_block;
			return (decompressed);
		}

		/* Decompress as much as we can in one pass. */
		ret = BZ2_bzDecompress(&(state->stream));
		__archive_read_filter_consume(self->upstream,
		    state->stream.next_in - read_buf);

		switch (ret) {
		case BZ_STREAM_END: /* Found end of stream. */
			switch (BZ2_bzDecompressEnd(&(state->stream))) {
			case BZ_OK:
				break;
			default:
				archive_set_error(&(self->archive->archive),
					  ARCHIVE_ERRNO_MISC,
					  "Failed to clean up decompressor");
				return (ARCHIVE_FATAL);
			}
			state->valid = 0;
			/* FALLTHROUGH */
		case BZ_OK: /* Decompressor made some progress. */
			/* If we filled our buffer, update stats and return. */
			if (state->stream.avail_out == 0) {
				*p = state->out_block;
				decompressed = state->stream.next_out
				    - state->out_block;
				return (decompressed);
			}
			break;
		default: /* Return an error. */
			archive_set_error(&self->archive->archive,
			    ARCHIVE_ERRNO_MISC, "bzip decompression failed");
			return (ARCHIVE_FATAL);
		}
	}
}