		iso9660->current_position = parent->offset;

	}



	step = (size_t)(((parent->size + iso9660->logical_block_size -1) /

	    iso9660->logical_block_size) * iso9660->logical_block_size);

	b = __archive_read_ahead(a, step, NULL);

	if (b == NULL) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

