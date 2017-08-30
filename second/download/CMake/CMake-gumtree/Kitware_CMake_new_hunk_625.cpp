	archive_entry_set_atime(entry, zip_entry->atime, 0);

	if ((zip->entry->mode & AE_IFMT) == AE_IFLNK) {
		size_t linkname_length;

		if (zip_entry->compressed_size > 64 * 1024) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Zip file with oversized link entry");
			return ARCHIVE_FATAL;
		}

		linkname_length = (size_t)zip_entry->compressed_size;

		archive_entry_set_size(entry, 0);
		p = __archive_read_ahead(a, linkname_length, NULL);
