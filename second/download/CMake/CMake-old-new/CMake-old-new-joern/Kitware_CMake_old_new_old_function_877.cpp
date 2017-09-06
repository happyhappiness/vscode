static int
archive_read_format_zip_seekable_read_header(struct archive_read *a,
	struct archive_entry *entry)
{
	struct zip *zip = (struct zip *)a->format->data;
	int r;

	a->archive.archive_format = ARCHIVE_FORMAT_ZIP;
	if (a->archive.archive_format_name == NULL)
		a->archive.archive_format_name = "ZIP";

	if (zip->zip_entries == NULL) {
		r = slurp_central_directory(a, zip);
		zip->entries_remaining = zip->central_directory_entries;
		if (r != ARCHIVE_OK)
			return r;
		zip->entry = zip->zip_entries;
	} else {
		++zip->entry;
	}

	if (zip->entries_remaining <= 0)
		return ARCHIVE_EOF;
	--zip->entries_remaining;

	/* TODO: If entries are sorted by offset within the file, we
	   should be able to skip here instead of seeking.  Skipping is
	   typically faster (easier for I/O layer to optimize). */
	__archive_read_seek(a, zip->entry->local_header_offset, SEEK_SET);
	zip->unconsumed = 0;
	r = zip_read_local_file_header(a, entry, zip);
	if (r != ARCHIVE_OK)
		return r;
	if ((zip->entry->mode & AE_IFMT) == AE_IFLNK) {
		const void *p;
		size_t linkname_length = archive_entry_size(entry);

		archive_entry_set_size(entry, 0);
		p = __archive_read_ahead(a, linkname_length, NULL);
		if (p == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Truncated Zip file");
			return ARCHIVE_FATAL;
		}

		if (archive_entry_copy_symlink_l(entry, p, linkname_length,
		    NULL) != 0) {
			/* NOTE: If the last argument is NULL, this will
			 * fail only by memeory allocation failure. */
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Symlink");
			return (ARCHIVE_FATAL);
		}
		/* TODO: handle character-set issues? */
	}
	return ARCHIVE_OK;
}