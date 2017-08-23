static int
common_setup(struct archive_write_filter *f)
{
	struct private_data *data;
	struct archive_write *a = (struct archive_write *)f->archive;
	data = calloc(1, sizeof(*data));
	if (data == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Out of memory");
		return (ARCHIVE_FATAL);
	}
	f->data = data;
	data->compression_level = LZMA_PRESET_DEFAULT;
	data->threads = 1;
	f->open = &archive_compressor_xz_open;
	f->close = archive_compressor_xz_close;
	f->free = archive_compressor_xz_free;
	f->options = &archive_compressor_xz_options;
	return (ARCHIVE_OK);
}