static int
archive_compressor_bzip2_close(struct archive_write_filter *f)
{
	struct private_data *data = (struct private_data *)f->data;
	int ret, r1;

	/* Finish compression cycle. */
	ret = drive_compressor(f, data, 1);
	if (ret == ARCHIVE_OK) {
		/* Write the last block */
		ret = __archive_write_filter(f->next_filter,
		    data->compressed,
		    data->compressed_buffer_size - data->stream.avail_out);
	}

	switch (BZ2_bzCompressEnd(&(data->stream))) {
	case BZ_OK:
		break;
	default:
		archive_set_error(f->archive, ARCHIVE_ERRNO_PROGRAMMER,
		    "Failed to clean up compressor");
		ret = ARCHIVE_FATAL;
	}

	r1 = __archive_write_close_filter(f->next_filter);
	return (r1 < ret ? r1 : ret);
}