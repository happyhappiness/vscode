{
	static const size_t out_block_size = 64 * 1024;
	void *out_block;
	struct private_data *state;
	int ret;

	state = (struct private_data *)calloc(sizeof(*state), 1);
	out_block = (unsigned char *)malloc(out_block_size);
	if (state == NULL || out_block == NULL) {
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for xz decompression");
		free(out_block);
		free(state);
		return (ARCHIVE_FATAL);
	}

	self->data = state;
	state->out_block_size = out_block_size;
	state->out_block = out_block;
	self->read = xz_filter_read;
	self->skip = NULL; /* not supported */
	self->close = xz_filter_close;

	state->stream.avail_in = 0;

	state->stream.next_out = state->out_block;
	state->stream.avail_out = state->out_block_size;

	state->crc32 = 0;
	if (self->code == ARCHIVE_FILTER_LZIP) {
		/*
		 * We have to read a lzip header and use it to initialize
		 * compression library, thus we cannot initialize the
		 * library for lzip here.
		 */
		state->in_stream = 0;
		return (ARCHIVE_OK);
	} else
		state->in_stream = 1;

	/* Initialize compression library. */
	if (self->code == ARCHIVE_FILTER_XZ)
		ret = lzma_stream_decoder(&(state->stream),
		    LZMA_MEMLIMIT,/* memlimit */
		    LZMA_CONCATENATED);
	else
		ret = lzma_alone_decoder(&(state->stream),
		    LZMA_MEMLIMIT);/* memlimit */

	if (ret == LZMA_OK)
		return (ARCHIVE_OK);

	/* Library setup failed: Choose an error message and clean up. */
	set_error(self, ret);

	free(state->out_block);
	free(state);
	self->data = NULL;
	return (ARCHIVE_FATAL);
}