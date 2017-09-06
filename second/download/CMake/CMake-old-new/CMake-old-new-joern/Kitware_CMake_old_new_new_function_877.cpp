static int
archive_read_format_zip_seekable_read_header(struct archive_read *a,
	struct archive_entry *entry)
{
	struct zip *zip = (struct zip *)a->format->data;
	struct zip_entry *rsrc;
	int r, ret = ARCHIVE_OK;

	a->archive.archive_format = ARCHIVE_FORMAT_ZIP;
	if (a->archive.archive_format_name == NULL)
		a->archive.archive_format_name = "ZIP";

	if (zip->zip_entries == NULL) {
		r = slurp_central_directory(a, zip);
		zip->entries_remaining = zip->central_directory_entries;
		if (r != ARCHIVE_OK)
			return r;
		/* Get first entry whose local header offset is lower than
		 * other entries in the archive file. */
		zip->entry =
		    (struct zip_entry *)ARCHIVE_RB_TREE_MIN(&zip->tree);
	} else if (zip->entry != NULL) {
		/* Get next entry in local header offset order. */
		zip->entry = (struct zip_entry *)__archive_rb_tree_iterate(
		    &zip->tree, &zip->entry->node, ARCHIVE_RB_DIR_RIGHT);
	}

	if (zip->entries_remaining <= 0 || zip->entry == NULL)
		return ARCHIVE_EOF;
	--zip->entries_remaining;

	if (zip->entry->rsrcname.s)
		rsrc = (struct zip_entry *)__archive_rb_tree_find_node(
		    &zip->tree_rsrc, zip->entry->rsrcname.s);
	else
		rsrc = NULL;

	/* File entries are sorted by the header offset, we should mostly
	 * use zip_read_consume to advance a read point to avoid redundant
	 * data reading.  */
	if (zip->offset < zip->entry->local_header_offset)
		zip_read_consume(a,
		    zip->entry->local_header_offset - zip->offset);
	else if (zip->offset != zip->entry->local_header_offset) {
		__archive_read_seek(a, zip->entry->local_header_offset,
			SEEK_SET);
		zip->offset = zip->entry->local_header_offset;
	}
	zip->unconsumed = 0;
	r = zip_read_local_file_header(a, entry, zip);
	if (r != ARCHIVE_OK)
		return r;
	if ((zip->entry->mode & AE_IFMT) == AE_IFLNK) {
		const void *p;
		struct archive_string_conv *sconv;
		size_t linkname_length = (size_t)archive_entry_size(entry);

		archive_entry_set_size(entry, 0);
		p = __archive_read_ahead(a, linkname_length, NULL);
		if (p == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Truncated Zip file");
			return ARCHIVE_FATAL;
		}

		sconv = zip->sconv;
		if (sconv == NULL && (zip->entry->flags & ZIP_UTF8_NAME))
			sconv = zip->sconv_utf8;
		if (sconv == NULL)
			sconv = zip->sconv_default;
		if (archive_entry_copy_symlink_l(entry, p, linkname_length,
		    sconv) != 0) {
			if (errno != ENOMEM && sconv == zip->sconv_utf8 &&
			    (zip->entry->flags & ZIP_UTF8_NAME))
			    archive_entry_copy_symlink_l(entry, p,
				linkname_length, NULL);
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for Symlink");
				return (ARCHIVE_FATAL);
			}
			/*
			 * Since there is no character-set regulation for
			 * symlink name, do not report the conversion error
			 * in an automatic conversion.
			 */
			if (sconv != zip->sconv_utf8 ||
			    (zip->entry->flags & ZIP_UTF8_NAME) == 0) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Symlink cannot be converted "
				    "from %s to current locale.",
				    archive_string_conversion_charset_name(
					sconv));
				ret = ARCHIVE_WARN;
			}
		}
	}
	if (rsrc) {
		int ret2 = zip_read_mac_metadata(a, entry, rsrc);
		if (ret2 < ret)
			ret = ret2;
	}
	return (ret);
}