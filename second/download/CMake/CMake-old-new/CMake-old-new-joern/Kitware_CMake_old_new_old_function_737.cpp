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
			}
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Can't translate Pathname '%s' to %s",
			    archive_entry_pathname(entry),
			    archive_string_conversion_charset_name(sconv));
			ret2 = ARCHIVE_WARN;
		}
		if (len > 0)
			archive_entry_set_pathname(l->entry, p);

		/*
		 * Although there is no character-set regulation for Symlink,
		 * it is suitable to convert a character-set of Symlinke to
		 * what those of the Pathname has been converted to.
		 */
		if (type == AE_IFLNK) {
			if (archive_entry_symlink_l(entry, &p, &len, sconv)) {
				if (errno == ENOMEM) {
					archive_entry_free(l->entry);
					free(l);
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate memory "
					    " for Symlink");
					return (ARCHIVE_FATAL);
				}
				/*
				 * Even if the strng conversion failed,
				 * we should not report the error since
				 * thre is no regulation for.
				 */
			} else if (len > 0)
				archive_entry_set_symlink(l->entry, p);
		}
	}
	/* If all characters in a filename are ASCII, Reset UTF-8 Name flag. */
	if ((l->flags & ZIP_FLAGS_UTF8_NAME) != 0 &&
	    is_all_ascii(archive_entry_pathname(l->entry)))
		l->flags &= ~ZIP_FLAGS_UTF8_NAME;

	/* Initialize the CRC variable and potentially the local crc32(). */
	l->crc32 = crc32(0, NULL, 0);
	if (type == AE_IFLNK) {
		const char *p = archive_entry_symlink(l->entry);
		if (p != NULL)
			size = strlen(p);
		else
			size = 0;
		zip->remaining_data_bytes = 0;
		archive_entry_set_size(l->entry, size);
		l->compression = COMPRESSION_STORE;
		l->compressed_size = size;
	} else {
		l->compression = zip->compression;
		l->compressed_size = 0;
	}
	l->next = NULL;
	if (zip->central_directory == NULL) {
		zip->central_directory = l;
	} else {
		zip->central_directory_end->next = l;
	}
	zip->central_directory_end = l;

	/* Store the offset of this header for later use in central
	 * directory. */
	l->offset = zip->written_bytes;

	memset(h, 0, sizeof(h));
	archive_le32enc(&h[LOCAL_FILE_HEADER_SIGNATURE],
		ZIP_SIGNATURE_LOCAL_FILE_HEADER);
	archive_le16enc(&h[LOCAL_FILE_HEADER_VERSION], ZIP_VERSION_EXTRACT);
	archive_le16enc(&h[LOCAL_FILE_HEADER_FLAGS], l->flags);
	archive_le16enc(&h[LOCAL_FILE_HEADER_COMPRESSION], l->compression);
	archive_le32enc(&h[LOCAL_FILE_HEADER_TIMEDATE],
		dos_time(archive_entry_mtime(entry)));
	archive_le16enc(&h[LOCAL_FILE_HEADER_FILENAME_LENGTH],
		(uint16_t)path_length(l->entry));

	switch (l->compression) {
	case COMPRESSION_STORE:
		/* Setting compressed and uncompressed sizes even when
		 * specification says to set to zero when using data
		 * descriptors. Otherwise the end of the data for an
		 * entry is rather difficult to find. */
		archive_le32enc(&h[LOCAL_FILE_HEADER_COMPRESSED_SIZE],
		    (uint32_t)size);
		archive_le32enc(&h[LOCAL_FILE_HEADER_UNCOMPRESSED_SIZE],
		    (uint32_t)size);
		break;
#ifdef HAVE_ZLIB_H
	case COMPRESSION_DEFLATE:
		archive_le32enc(&h[LOCAL_FILE_HEADER_UNCOMPRESSED_SIZE],
		    (uint32_t)size);

		zip->stream.zalloc = Z_NULL;
		zip->stream.zfree = Z_NULL;
		zip->stream.opaque = Z_NULL;
		zip->stream.next_out = zip->buf;
		zip->stream.avail_out = (uInt)zip->len_buf;
		if (deflateInit2(&zip->stream, Z_DEFAULT_COMPRESSION,
		    Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY) != Z_OK) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't init deflate compressor");
			return (ARCHIVE_FATAL);
		}
		break;
#endif
	}

	/* Formatting extra data. */
	archive_le16enc(&h[LOCAL_FILE_HEADER_EXTRA_LENGTH], sizeof(e));
	archive_le16enc(&e[EXTRA_DATA_LOCAL_TIME_ID],
		ZIP_SIGNATURE_EXTRA_TIMESTAMP);
	archive_le16enc(&e[EXTRA_DATA_LOCAL_TIME_SIZE], 1 + 4 * 3);
	e[EXTRA_DATA_LOCAL_TIME_FLAG] = 0x07;
	archive_le32enc(&e[EXTRA_DATA_LOCAL_MTIME],
	    (uint32_t)archive_entry_mtime(entry));
	archive_le32enc(&e[EXTRA_DATA_LOCAL_ATIME],
	    (uint32_t)archive_entry_atime(entry));
	archive_le32enc(&e[EXTRA_DATA_LOCAL_CTIME],
	    (uint32_t)archive_entry_ctime(entry));

	archive_le16enc(&e[EXTRA_DATA_LOCAL_UNIX_ID],
		ZIP_SIGNATURE_EXTRA_NEW_UNIX);
	archive_le16enc(&e[EXTRA_DATA_LOCAL_UNIX_SIZE], 1 + (1 + 4) * 2);
	e[EXTRA_DATA_LOCAL_UNIX_VERSION] = 1;
	e[EXTRA_DATA_LOCAL_UNIX_UID_SIZE] = 4;
	archive_le32enc(&e[EXTRA_DATA_LOCAL_UNIX_UID],
		(uint32_t)archive_entry_uid(entry));
	e[EXTRA_DATA_LOCAL_UNIX_GID_SIZE] = 4;
	archive_le32enc(&e[EXTRA_DATA_LOCAL_UNIX_GID],
		(uint32_t)archive_entry_gid(entry));

	archive_le32enc(&d[DATA_DESCRIPTOR_UNCOMPRESSED_SIZE],
	    (uint32_t)size);

	ret = __archive_write_output(a, h, sizeof(h));
	if (ret != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	zip->written_bytes += sizeof(h);

	ret = write_path(l->entry, a);
	if (ret <= ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	zip->written_bytes += ret;

	ret = __archive_write_output(a, e, sizeof(e));
	if (ret != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	zip->written_bytes += sizeof(e);

	if (type == AE_IFLNK) {
		const unsigned char *p;

		p = (const unsigned char *)archive_entry_symlink(l->entry);
		ret = __archive_write_output(a, p, (size_t)size);
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		zip->written_bytes += size;
		l->crc32 = crc32(l->crc32, p, (unsigned)size);
	}

	if (ret2 != ARCHIVE_OK)
		return (ret2);
	return (ARCHIVE_OK);
}