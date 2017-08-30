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



static ssize_t

archive_write_zip_data(struct archive_write *a, const void *buff, size_t s)

{

	int ret;

	struct zip *zip = a->format_data;

	struct zip_file_header_link *l = zip->central_directory_end;



	if ((int64_t)s > zip->remaining_data_bytes)

		s = (size_t)zip->remaining_data_bytes;



	if (s == 0) return 0;



	switch (l->compression) {

	case COMPRESSION_STORE:

		ret = __archive_write_output(a, buff, s);

		if (ret != ARCHIVE_OK) return (ret);

		zip->written_bytes += s;

		zip->remaining_data_bytes -= s;

		l->compressed_size += s;

		l->crc32 = crc32(l->crc32, buff, (unsigned)s);

		return (s);

#if HAVE_ZLIB_H

	case COMPRESSION_DEFLATE:

		zip->stream.next_in = (unsigned char*)(uintptr_t)buff;

