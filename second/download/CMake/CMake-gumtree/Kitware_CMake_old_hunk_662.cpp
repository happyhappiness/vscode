static int
archive_write_zip_header(struct archive_write *a, struct archive_entry *entry)
{
	struct zip *zip;
	uint8_t h[SIZE_LOCAL_FILE_HEADER];
	uint8_t e[SIZE_EXTRA_DATA_LOCAL];
	uint8_t *d;
	struct zip_file_header_link *l;
	struct archive_string_conv *sconv;
	int ret, ret2 = ARCHIVE_OK;
	int64_t size;
	mode_t type;

	/* Entries other than a regular file or a folder are skipped. */
	type = archive_entry_filetype(entry);
	if (type != AE_IFREG && type != AE_IFDIR && type != AE_IFLNK) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Filetype not supported");
		return ARCHIVE_FAILED;
	};

	/* Directory entries should have a size of 0. */
	if (type == AE_IFDIR)
		archive_entry_set_size(entry, 0);

	zip = a->format_data;
	/* Setup default conversion. */
	if (zip->opt_sconv == NULL && !zip->init_default_conversion) {
		zip->sconv_default =
		    archive_string_default_conversion_for_write(&(a->archive));
		zip->init_default_conversion = 1;
	}

	if (zip->flags == 0) {
		/* Initialize the general purpose flags. */
		zip->flags = ZIP_FLAGS;
		if (zip->opt_sconv != NULL) {
			if (strcmp(archive_string_conversion_charset_name(
			    zip->opt_sconv), "UTF-8") == 0)
				zip->flags |= ZIP_FLAGS_UTF8_NAME;
#if HAVE_NL_LANGINFO
		} else if (strcmp(nl_langinfo(CODESET), "UTF-8") == 0) {
			zip->flags |= ZIP_FLAGS_UTF8_NAME;
#endif
		}
	}
	d = zip->data_descriptor;
	size = archive_entry_size(entry);
	zip->remaining_data_bytes = size;

	/* Append archive entry to the central directory data. */
	l = (struct zip_file_header_link *) malloc(sizeof(*l));
	if (l == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate zip header data");
		return (ARCHIVE_FATAL);
	}
#if defined(_WIN32) && !defined(__CYGWIN__)
	/* Make sure the path separators in pahtname, hardlink and symlink
	 * are all slash '/', not the Windows path separator '\'. */
	l->entry = __la_win_entry_in_posix_pathseparator(entry);
	if (l->entry == entry)
		l->entry = archive_entry_clone(entry);
#else
	l->entry = archive_entry_clone(entry);
#endif
	if (l->entry == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate zip header data");
		free(l);
		return (ARCHIVE_FATAL);
	}
	l->flags = zip->flags;
	if (zip->opt_sconv != NULL)
		sconv = zip->opt_sconv;
	else
		sconv = zip->sconv_default;
	if (sconv != NULL) {
		const char *p;
		size_t len;

		if (archive_entry_pathname_l(entry, &p, &len, sconv) != 0) {
			if (errno == ENOMEM) {
				archive_entry_free(l->entry);
				free(l);
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for Pathname");
				return (ARCHIVE_FATAL);
