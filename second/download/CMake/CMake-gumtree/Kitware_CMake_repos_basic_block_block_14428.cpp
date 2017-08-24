{
	struct private_data *data = (struct private_data *)f->data;
	int ret;

	ret = __archive_write_open_filter(f->next_filter);
	if (ret != 0)
		return (ret);

	if (data->compressed == NULL) {
		size_t bs = 65536, bpb;
		if (f->archive->magic == ARCHIVE_WRITE_MAGIC) {
			/* Buffer size should be a multiple number of the of bytes
			 * per block for performance. */
			bpb = archive_write_get_bytes_per_block(f->archive);
			if (bpb > bs)
				bs = bpb;
			else if (bpb != 0)
				bs -= bs % bpb;
		}
		data->compressed_buffer_size = bs;
		data->compressed
		    = (char *)malloc(data->compressed_buffer_size);
		if (data->compressed == NULL) {
			archive_set_error(f->archive, ENOMEM,
			    "Can't allocate data for compression buffer");
			return (ARCHIVE_FATAL);
		}
	}

	memset(&data->stream, 0, sizeof(data->stream));
	data->stream.next_out = data->compressed;
	data->stream.avail_out = data->compressed_buffer_size;
	f->write = archive_compressor_bzip2_write;

	/* Initialize compression library */
	ret = BZ2_bzCompressInit(&(data->stream),
	    data->compression_level, 0, 30);
	if (ret == BZ_OK) {
		f->data = data;
		return (ARCHIVE_OK);
	}

	/* Library setup failed: clean up. */
	archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
	    "Internal error initializing compression library");

	/* Override the error message if we know what really went wrong. */
	switch (ret) {
	case BZ_PARAM_ERROR:
		archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library: "
		    "invalid setup parameter");
		break;
	case BZ_MEM_ERROR:
		archive_set_error(f->archive, ENOMEM,
		    "Internal error initializing compression library: "
		    "out of memory");
		break;
	case BZ_CONFIG_ERROR:
		archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing compression library: "
		    "mis-compiled library");
		break;
	}

	return (ARCHIVE_FATAL);

}