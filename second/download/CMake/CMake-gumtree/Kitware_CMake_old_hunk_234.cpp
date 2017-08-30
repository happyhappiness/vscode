	/* Make sure we have a whole block. */

	read_buf = __archive_read_filter_ahead(self->upstream,

	    4 + compressed, NULL);

	ret = LZ4_decompress_safe(read_buf + 4, state->out_block,

	    compressed, (int)state->out_block_size);

	if (ret < 0) {
