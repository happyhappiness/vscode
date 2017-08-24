	if (AE_IFREG != (zip->entry->mode & AE_IFMT))
		return (ARCHIVE_EOF);

	if (zip->entry->zip_flags & (ZIP_ENCRYPTED | ZIP_STRONG_ENCRYPTED)) {
		zip->has_encrypted_entries = 1;
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Encrypted file is unsupported");
		return (ARCHIVE_FAILED);
	}

	__archive_read_consume(a, zip->unconsumed);
	zip->unconsumed = 0;

	switch(zip->entry->compression) {
	case 0:  /* No compression. */
		r =  zip_read_data_none(a, buff, size, offset);
