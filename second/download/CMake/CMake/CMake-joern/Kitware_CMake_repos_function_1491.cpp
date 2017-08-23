static int
archive_compressor_gzip_close(struct archive_write_filter *f)
{
	unsigned char trailer[8];
	struct private_data *data = (struct private_data *)f->data;
	int ret, r1;

	/* Finish compression cycle */
	ret = drive_compressor(f, data, 1);
	if (ret == ARCHIVE_OK) {
		/* Write the last compressed data. */
		ret = __archive_write_filter(f->next_filter,
		    data->compressed,
		    data->compressed_buffer_size - data->stream.avail_out);
	}
	if (ret == ARCHIVE_OK) {
		/* Build and write out 8-byte trailer. */
		trailer[0] = (uint8_t)(data->crc)&0xff;
		trailer[1] = (uint8_t)(data->crc >> 8)&0xff;
		trailer[2] = (uint8_t)(data->crc >> 16)&0xff;
		trailer[3] = (uint8_t)(data->crc >> 24)&0xff;
		trailer[4] = (uint8_t)(data->total_in)&0xff;
		trailer[5] = (uint8_t)(data->total_in >> 8)&0xff;
		trailer[6] = (uint8_t)(data->total_in >> 16)&0xff;
		trailer[7] = (uint8_t)(data->total_in >> 24)&0xff;
		ret = __archive_write_filter(f->next_filter, trailer, 8);
	}

	switch (deflateEnd(&(data->stream))) {
	case Z_OK:
		break;
	default:
		archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
		    "Failed to clean up compressor");
		ret = ARCHIVE_FATAL;
	}
	r1 = __archive_write_close_filter(f->next_filter);
	return (r1 < ret ? r1 : ret);
}