{
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