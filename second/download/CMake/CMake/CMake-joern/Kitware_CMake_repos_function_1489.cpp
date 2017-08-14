static int
archive_compressor_gzip_open(struct archive_write_filter *f)
{
	struct private_data *data = (struct private_data *)f->data;
	int ret;

	ret = __archive_write_open_filter(f->next_filter);
	if (ret != ARCHIVE_OK)
		return (ret);

	if (data->compressed == NULL) {
		size_t bs = 65536, bpb;
		if (f->archive->magic == ARCHIVE_WRITE_MAGIC) {
			/* Buffer size should be a multiple number of
			 * the of bytes per block for performance. */
			bpb = archive_write_get_bytes_per_block(f->archive);
			if (bpb > bs)
				bs = bpb;
			else if (bpb != 0)
				bs -= bs % bpb;
		}
		data->compressed_buffer_size = bs;
		data->compressed
		    = (unsigned char *)malloc(data->compressed_buffer_size);
		if (data->compressed == NULL) {
			archive_set_error(f->archive, ENOMEM,
			    "Can't allocate data for compression buffer");
			return (ARCHIVE_FATAL);
		}
	}

	data->crc = crc32(0L, NULL, 0);
	data->stream.next_out = data->compressed;
	data->stream.avail_out = (uInt)data->compressed_buffer_size;

	/* Prime output buffer with a gzip header. */
	data->compressed[0] = 0x1f; /* GZip signature bytes */
	data->compressed[1] = 0x8b;
	data->compressed[2] = 0x08; /* "Deflate" compression */
	data->compressed[3] = 0; /* No options */
	if (data->timestamp >= 0) {
		time_t t = time(NULL);
		data->compressed[4] = (uint8_t)(t)&0xff;  /* Timestamp */
		data->compressed[5] = (uint8_t)(t>>8)&0xff;
		data->compressed[6] = (uint8_t)(t>>16)&0xff;
		data->compressed[7] = (uint8_t)(t>>24)&0xff;
	} else
		memset(&data->compressed[4], 0, 4);
	data->compressed[8] = 0; /* No deflate options */
	data->compressed[9] = 3; /* OS=Unix */
	data->stream.next_out += 10;
	data->stream.avail_out -= 10;

	f->write = archive_compressor_gzip_write;

	/* Initialize compression library. */
	ret = deflateInit2(&(data->stream),
	    data->compression_level,
	    Z_DEFLATED,
	    -15 /* < 0 to suppress zlib header */,
	    8,
	    Z_DEFAULT_STRATEGY);

	if (ret == Z_OK) {
		f->data = data;
		return (ARCHIVE_OK);
	}

	/* Library setup failed: clean up. */
	archive_set_error(f->archive, ARCHIVE_ERRNO_MISC, "Internal error "
	    "initializing compression library");

	/* Override the error message if we know what really went wrong. */
	switch (ret) {
	case Z_STREAM_ERROR:
		archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing "
		    "compression library: invalid setup parameter");
		break;
	case Z_MEM_ERROR:
		archive_set_error(f->archive, ENOMEM,
		    "Internal error initializing compression library");
		break;
	case Z_VERSION_ERROR:
		archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
		    "Internal error initializing "
		    "compression library: invalid library version");
		break;
	}

	return (ARCHIVE_FATAL);
}