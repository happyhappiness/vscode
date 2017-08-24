{
	struct write_lzop *data = (struct write_lzop *)f->data;
	const char *p = buff;
	int r;

	do {
		if (data->uncompressed_avail_bytes > length) {
			memcpy(data->uncompressed
				+ data->uncompressed_buffer_size
				- data->uncompressed_avail_bytes,
			    p, length);
			data->uncompressed_avail_bytes -= length;
			return (ARCHIVE_OK);
		}

		memcpy(data->uncompressed + data->uncompressed_buffer_size
			- data->uncompressed_avail_bytes,
		    p, data->uncompressed_avail_bytes);
		length -= data->uncompressed_avail_bytes;
		p += data->uncompressed_avail_bytes;
		data->uncompressed_avail_bytes = 0;

		r = drive_compressor(f);
		if (r != ARCHIVE_OK) return (r);
		data->uncompressed_avail_bytes = BLOCK_SIZE;
	} while (length);

	return (ARCHIVE_OK);
}