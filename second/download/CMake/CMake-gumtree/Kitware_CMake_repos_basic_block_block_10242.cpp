{
	struct private_data *state;

	self->code = ARCHIVE_FILTER_LZ4;
	self->name = "lz4";

	state = (struct private_data *)calloc(sizeof(*state), 1);
	if (state == NULL) {
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for lz4 decompression");
		return (ARCHIVE_FATAL);
	}

	self->data = state;
	state->stage = SELECT_STREAM;
	self->read = lz4_filter_read;
	self->skip = NULL; /* not supported */
	self->close = lz4_filter_close;

	return (ARCHIVE_OK);
}