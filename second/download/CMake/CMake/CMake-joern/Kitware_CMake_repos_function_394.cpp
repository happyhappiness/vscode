int
archive_write_add_filter_b64encode(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct archive_write_filter *f = __archive_write_allocate_filter(_a);
	struct private_b64encode *state;

	archive_check_magic(&a->archive, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_add_filter_uu");

	state = (struct private_b64encode *)calloc(1, sizeof(*state));
	if (state == NULL) {
		archive_set_error(f->archive, ENOMEM,
		    "Can't allocate data for b64encode filter");
		return (ARCHIVE_FATAL);
	}
	archive_strcpy(&state->name, "-");
	state->mode = 0644;

	f->data = state;
	f->name = "b64encode";
	f->code = ARCHIVE_FILTER_UU;
	f->open = archive_filter_b64encode_open;
	f->options = archive_filter_b64encode_options;
	f->write = archive_filter_b64encode_write;
	f->close = archive_filter_b64encode_close;
	f->free = archive_filter_b64encode_free;

	return (ARCHIVE_OK);
}