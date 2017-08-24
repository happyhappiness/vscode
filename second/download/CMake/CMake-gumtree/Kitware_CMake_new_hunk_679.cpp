static int
archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
{
	unsigned char local_header[32];
	unsigned char local_extra[128];
	struct zip *zip = a->format_data;
	unsigned char *e;
	unsigned char *cd_extra;
	size_t filename_length;
	const char *symlink = NULL;
	size_t symlink_size = 0;
	struct archive_string_conv *sconv = get_sconv(a, zip);
	int ret, ret2 = ARCHIVE_OK;
	int64_t size;
	mode_t type;
	int version_needed = 10;

	/* Ignore types of entries that we don't support. */
	type = archive_entry_filetype(entry);
	if (type != AE_IFREG && type != AE_IFDIR && type != AE_IFLNK) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Filetype not supported");
		return ARCHIVE_FAILED;
	};

	/* If we're not using Zip64, reject large files. */
	if (zip->flags & ZIP_FLAG_AVOID_ZIP64) {
		/* Reject entries over 4GB. */
		if (archive_entry_size_is_set(entry)
		    && (archive_entry_size(entry) > 0xffffffff)) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Files > 4GB require Zip64 extensions");
			return ARCHIVE_FAILED;
		}
		/* Reject entries if archive is > 4GB. */
		if (zip->written_bytes > 0xffffffff) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Archives > 4GB require Zip64 extensions");
			return ARCHIVE_FAILED;
		}
	}

	/* Only regular files can have size > 0. */
	if (type != AE_IFREG)
		archive_entry_set_size(entry, 0);


	/* Reset information from last entry. */
	zip->entry_offset = zip->written_bytes;
	zip->entry_uncompressed_limit = INT64_MAX;
	zip->entry_compressed_size = 0;
	zip->entry_uncompressed_size = 0;
	zip->entry_compressed_written = 0;
	zip->entry_uncompressed_written = 0;
	zip->entry_flags = 0;
	zip->entry_uses_zip64 = 0;
	zip->entry_crc32 = zip->crc32func(0, NULL, 0);
	if (zip->entry != NULL) {
		archive_entry_free(zip->entry);
		zip->entry = NULL;
	}

#if defined(_WIN32) && !defined(__CYGWIN__)
	/* Make sure the path separators in pahtname, hardlink and symlink
	 * are all slash '/', not the Windows path separator '\'. */
	zip->entry = __la_win_entry_in_posix_pathseparator(entry);
	if (zip->entry == entry)
		zip->entry = archive_entry_clone(entry);
#else
	zip->entry = archive_entry_clone(entry);
#endif
	if (zip->entry == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate zip header data");
		return (ARCHIVE_FATAL);
	}

	if (sconv != NULL) {
		const char *p;
		size_t len;

		if (archive_entry_pathname_l(entry, &p, &len, sconv) != 0) {
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for Pathname");
				return (ARCHIVE_FATAL);
