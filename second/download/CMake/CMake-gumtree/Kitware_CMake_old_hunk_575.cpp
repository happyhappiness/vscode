	archive_entry_set_atime(entry, zip_entry->atime, 0);



	if ((zip->entry->mode & AE_IFMT) == AE_IFLNK) {

		size_t linkname_length = zip_entry->compressed_size;



		archive_entry_set_size(entry, 0);

		p = __archive_read_ahead(a, linkname_length, NULL);

