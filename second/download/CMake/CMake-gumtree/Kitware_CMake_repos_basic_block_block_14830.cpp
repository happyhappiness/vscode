(a->uncompressed_buffer == NULL) {
			new_block = malloc(MAX_DECMPFS_BLOCK_SIZE);
			if (new_block == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for decmpfs");
				return (ARCHIVE_FATAL);
			}
			a->uncompressed_buffer = new_block;
		}