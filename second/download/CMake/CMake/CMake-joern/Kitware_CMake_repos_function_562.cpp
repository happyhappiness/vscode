static int
bzip2_reader_init(struct archive_read_filter *self)
{
	static const size_t out_block_size = 64 * 1024;
	void *out_block;
	struct private_data *state;

	self->code = ARCHIVE_FILTER_BZIP2;
	self->name = "bzip2";

	state = (struct private_data *)calloc(sizeof(*state), 1);
	out_block = (unsigned char *)malloc(out_block_size);
	if (state == NULL || out_block == NULL) {
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for bzip2 decompression");
		free(out_block);
		free(state);
		return (ARCHIVE_FATAL);
	}

	self->data = state;
	state->out_block_size = out_block_size;
	state->out_block = out_block;
	self->read = bzip2_filter_read;
	self->skip = NULL; /* not supported */
	self->close = bzip2_filter_close;

	return (ARCHIVE_OK);
}