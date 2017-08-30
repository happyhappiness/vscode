		return (NULL);
	}

	/* Sanity check that this entry does not create a cycle. */
	offset = iso9660->logical_block_size * (uint64_t)location;
	for (filep = parent; filep != NULL; filep = filep->parent) {
		if (filep->offset == offset) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
			    "Directory structure contains loop");
			return (NULL);
		}
	}

	/* Create a new file entry and copy data from the ISO dir record. */
	file = (struct file_info *)calloc(1, sizeof(*file));
	if (file == NULL) {
