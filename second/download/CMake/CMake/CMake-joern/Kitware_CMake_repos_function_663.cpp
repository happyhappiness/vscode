static int
gzip_bidder_init(struct archive_read_filter *self)
{
	struct private_data *state;
	static const size_t out_block_size = 64 * 1024;
	void *out_block;

	self->code = ARCHIVE_FILTER_GZIP;
	self->name = "gzip";

	state = (struct private_data *)calloc(sizeof(*state), 1);
	out_block = (unsigned char *)malloc(out_block_size);
	if (state == NULL || out_block == NULL) {
		free(out_block);
		free(state);
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for gzip decompression");
		return (ARCHIVE_FATAL);
	}

	self->data = state;
	state->out_block_size = out_block_size;
	state->out_block = out_block;
	self->read = gzip_filter_read;
	self->skip = NULL; /* not supported */
	self->close = gzip_filter_close;

	state->in_stream = 0; /* We're not actually within a stream yet. */

	return (ARCHIVE_OK);
}