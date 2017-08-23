static int
drive_compressor(struct archive_write_filter *f)
{
	struct write_lzop *data = (struct write_lzop *)f->data;
	unsigned char *p;
	const int block_info_bytes = 12;
	int header_bytes, r;
	lzo_uint usize, csize;
	uint32_t checksum;

	if (!data->header_written) {
		header_bytes = make_header(f);
		data->header_written = 1;
	} else
		header_bytes = 0;
	p = data->compressed;

	usize = (lzo_uint)
	    (data->uncompressed_buffer_size - data->uncompressed_avail_bytes);
	csize = 0;
	switch (data->method) {
	default:
	case METHOD_LZO1X_1:
		r = lzo1x_1_compress(data->uncompressed, usize,
			p + header_bytes + block_info_bytes, &csize,
			data->work_buffer);
		break;
	case METHOD_LZO1X_1_15:
		r = lzo1x_1_15_compress(data->uncompressed, usize,
			p + header_bytes + block_info_bytes, &csize,
			data->work_buffer);
		break;
	case METHOD_LZO1X_999:
		r = lzo1x_999_compress_level(data->uncompressed, usize,
			p + header_bytes + block_info_bytes, &csize,
			data->work_buffer, NULL, 0, 0, data->level);
		break;
	}
	if (r != LZO_E_OK) {
		archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
		    "Lzop compression failed: returned status %d", r);
		return (ARCHIVE_FATAL);
	}

	/* Store uncompressed size. */
	archive_be32enc(p + header_bytes, (uint32_t)usize);
	/* Store the checksum of the uncompressed data. */
	checksum = lzo_adler32(1, data->uncompressed, usize);
	archive_be32enc(p + header_bytes + 8, checksum);

	if (csize < usize) {
		/* Store compressed size. */
		archive_be32enc(p + header_bytes + 4, (uint32_t)csize);
		r = __archive_write_filter(f->next_filter, data->compressed,
			header_bytes + block_info_bytes + csize);
	} else {
		/*
		 * This case, we output uncompressed data instead.
		 */
		/* Store uncompressed size as compressed size. */
		archive_be32enc(p + header_bytes + 4, (uint32_t)usize);
		r = __archive_write_filter(f->next_filter, data->compressed,
			header_bytes + block_info_bytes);
		if (r != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		r = __archive_write_filter(f->next_filter, data->uncompressed,
			usize);
	}

	if (r != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	return (ARCHIVE_OK);
}