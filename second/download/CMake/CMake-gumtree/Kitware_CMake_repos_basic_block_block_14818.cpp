{
		size_t block_size;

		block_size = COMPRESSED_W_SIZE + RSRC_F_SIZE +
		    + compressBound(MAX_DECMPFS_BLOCK_SIZE);
		a->compressed_buffer = malloc(block_size);
		if (a->compressed_buffer == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Resource Fork");
			return (ARCHIVE_FATAL);
		}
		a->compressed_buffer_size = block_size;
		a->compressed_buffer_remaining = block_size;
	}