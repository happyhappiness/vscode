static int
lzop_bidder_init(struct archive_read_filter *self)
{
	struct read_lzop *state;

	self->code = ARCHIVE_FILTER_LZOP;
	self->name = "lzop";

	state = (struct read_lzop *)calloc(sizeof(*state), 1);
	if (state == NULL) {
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for lzop decompression");
		return (ARCHIVE_FATAL);
	}

	self->data = state;
	self->read = lzop_filter_read;
	self->skip = NULL; /* not supported */
	self->close = lzop_filter_close;

	return (ARCHIVE_OK);
}