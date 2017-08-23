static int
archive_write_lzop_open(struct archive_write_filter *f)
{
	struct write_lzop *data = (struct write_lzop *)f->data;
	int ret;

	ret = __archive_write_open_filter(f->next_filter);
	if (ret != ARCHIVE_OK)
		return (ret);

	switch (data->compression_level) {
	case 1:
		data->method = METHOD_LZO1X_1_15; data->level = 1; break;
	default:
	case 2: case 3: case 4: case 5: case 6:
		data->method = METHOD_LZO1X_1; data->level = 5; break;
	case 7:
		data->method = METHOD_LZO1X_999; data->level = 7; break;
	case 8:
		data->method = METHOD_LZO1X_999; data->level = 8; break;
	case 9:
		data->method = METHOD_LZO1X_999; data->level = 9; break;
	}
	switch (data->method) {
	case METHOD_LZO1X_1:
		data->work_buffer_size = LZO1X_1_MEM_COMPRESS; break;
	case METHOD_LZO1X_1_15:
		data->work_buffer_size = LZO1X_1_15_MEM_COMPRESS; break;
	case METHOD_LZO1X_999:
		data->work_buffer_size = LZO1X_999_MEM_COMPRESS; break;
	}
	if (data->work_buffer == NULL) {
		data->work_buffer = (lzo_voidp)malloc(data->work_buffer_size);
		if (data->work_buffer == NULL) {
			archive_set_error(f->archive, ENOMEM,
			    "Can't allocate data for compression buffer");
			return (ARCHIVE_FATAL);
		}
	}
	if (data->compressed == NULL) {
		data->compressed_buffer_size = sizeof(header) +
		    BLOCK_SIZE + (BLOCK_SIZE >> 4) + 64 + 3;
		data->compressed = (unsigned char *)
		    malloc(data->compressed_buffer_size);
		if (data->compressed == NULL) {
			archive_set_error(f->archive, ENOMEM,
			    "Can't allocate data for compression buffer");
			return (ARCHIVE_FATAL);
		}
	}
	if (data->uncompressed == NULL) {
		data->uncompressed_buffer_size = BLOCK_SIZE;
		data->uncompressed = (unsigned char *)
		    malloc(data->uncompressed_buffer_size);
		if (data->uncompressed == NULL) {
			archive_set_error(f->archive, ENOMEM,
			    "Can't allocate data for compression buffer");
			return (ARCHIVE_FATAL);
		}
		data->uncompressed_avail_bytes = BLOCK_SIZE;
	}
	return (ARCHIVE_OK);
}