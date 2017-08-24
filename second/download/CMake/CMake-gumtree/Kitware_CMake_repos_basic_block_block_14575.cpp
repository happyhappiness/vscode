{
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