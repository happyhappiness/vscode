					zip->len_buf);

				if (ret != ARCHIVE_OK)

					return (ret);

				l->compressed_size += zip->len_buf;

				zip->written_bytes += zip->len_buf;

				zip->stream.next_out = zip->buf;

				zip->stream.avail_out = (uInt)zip->len_buf;

			}

		} while (zip->stream.avail_in != 0);

		zip->remaining_data_bytes -= s;

		/* If we have it, use zlib's fast crc32() */

		l->crc32 = crc32(l->crc32, buff, (uInt)s);

		return (s);

#endif



	default:

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Invalid ZIP compression type");

		return ARCHIVE_FATAL;

	}

}



static int

archive_write_zip_finish_entry(struct archive_write *a)

{

	/* Write the data descripter after file data has been written. */

	int ret;

	struct zip *zip = a->format_data;

	uint8_t *d = zip->data_descriptor;

	struct zip_file_header_link *l = zip->central_directory_end;

#if HAVE_ZLIB_H

	size_t reminder;

#endif



	switch(l->compression) {

	case COMPRESSION_STORE:

		break;

#if HAVE_ZLIB_H

	case COMPRESSION_DEFLATE:

		for (;;) {

			ret = deflate(&zip->stream, Z_FINISH);

			if (ret == Z_STREAM_ERROR)

				return (ARCHIVE_FATAL);

			reminder = zip->len_buf - zip->stream.avail_out;

			ret = __archive_write_output(a, zip->buf, reminder);

			if (ret != ARCHIVE_OK)

				return (ret);

			l->compressed_size += reminder;

			zip->written_bytes += reminder;

			zip->stream.next_out = zip->buf;

			if (zip->stream.avail_out != 0)

				break;

			zip->stream.avail_out = (uInt)zip->len_buf;

		}

		deflateEnd(&zip->stream);

		break;

#endif

	}



	archive_le32enc(&d[DATA_DESCRIPTOR_CRC32], l->crc32);

	archive_le32enc(&d[DATA_DESCRIPTOR_COMPRESSED_SIZE],

		(uint32_t)l->compressed_size);

	ret = __archive_write_output(a, d, SIZE_DATA_DESCRIPTOR);

	if (ret != ARCHIVE_OK)

		return (ARCHIVE_FATAL);

	zip->written_bytes += SIZE_DATA_DESCRIPTOR;

	return (ARCHIVE_OK);

}



static int

archive_write_zip_close(struct archive_write *a)

{

	struct zip *zip;

	struct zip_file_header_link *l;

	uint8_t h[SIZE_FILE_HEADER];

	uint8_t end[SIZE_CENTRAL_DIRECTORY_END];

	uint8_t e[SIZE_EXTRA_DATA_CENTRAL];

	int64_t offset_start, offset_end;

	int entries;

	int ret;



	zip = a->format_data;

	l = zip->central_directory;



	/*

	 * Formatting central directory file header fields that are

	 * fixed for all entries.

	 * Fields not used (and therefor 0) are:

	 *

	 *   - comment_length

	 *   - disk_number

	 *   - attributes_internal

	 */

	memset(h, 0, sizeof(h));

	archive_le32enc(&h[FILE_HEADER_SIGNATURE], ZIP_SIGNATURE_FILE_HEADER);

	archive_le16enc(&h[FILE_HEADER_VERSION_BY], ZIP_VERSION_BY);

	archive_le16enc(&h[FILE_HEADER_VERSION_EXTRACT], ZIP_VERSION_EXTRACT);



	entries = 0;

	offset_start = zip->written_bytes;



	/* Formatting individual header fields per entry and

	 * writing each entry. */

	while (l != NULL) {

		archive_le16enc(&h[FILE_HEADER_FLAGS], l->flags);

		archive_le16enc(&h[FILE_HEADER_COMPRESSION], l->compression);

		archive_le32enc(&h[FILE_HEADER_TIMEDATE],

			dos_time(archive_entry_mtime(l->entry)));

		archive_le32enc(&h[FILE_HEADER_CRC32], l->crc32);

		archive_le32enc(&h[FILE_HEADER_COMPRESSED_SIZE],

			(uint32_t)l->compressed_size);

		archive_le32enc(&h[FILE_HEADER_UNCOMPRESSED_SIZE],

			(uint32_t)archive_entry_size(l->entry));

		archive_le16enc(&h[FILE_HEADER_FILENAME_LENGTH],

			(uint16_t)path_length(l->entry));

		archive_le16enc(&h[FILE_HEADER_EXTRA_LENGTH], sizeof(e));

		archive_le16enc(&h[FILE_HEADER_ATTRIBUTES_EXTERNAL+2],

			archive_entry_mode(l->entry));

		archive_le32enc(&h[FILE_HEADER_OFFSET], (uint32_t)l->offset);



		/* Formatting extra data. */

		archive_le16enc(&e[EXTRA_DATA_CENTRAL_TIME_ID],

			ZIP_SIGNATURE_EXTRA_TIMESTAMP);

		archive_le16enc(&e[EXTRA_DATA_CENTRAL_TIME_SIZE], 1 + 4);

		e[EXTRA_DATA_CENTRAL_TIME_FLAG] = 0x07;

		archive_le32enc(&e[EXTRA_DATA_CENTRAL_MTIME],

			(uint32_t)archive_entry_mtime(l->entry));

		archive_le16enc(&e[EXTRA_DATA_CENTRAL_UNIX_ID],

			ZIP_SIGNATURE_EXTRA_NEW_UNIX);

		archive_le16enc(&e[EXTRA_DATA_CENTRAL_UNIX_SIZE], 0x0000);



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



		l = l->next;

		entries++;

	}

	offset_end = zip->written_bytes;



	/* Formatting end of central directory. */

	memset(end, 0, sizeof(end));

	archive_le32enc(&end[CENTRAL_DIRECTORY_END_SIGNATURE],

		ZIP_SIGNATURE_CENTRAL_DIRECTORY_END);

	archive_le16enc(&end[CENTRAL_DIRECTORY_END_ENTRIES_DISK], entries);

	archive_le16enc(&end[CENTRAL_DIRECTORY_END_ENTRIES], entries);

	archive_le32enc(&end[CENTRAL_DIRECTORY_END_SIZE],

		(uint32_t)(offset_end - offset_start));

	archive_le32enc(&end[CENTRAL_DIRECTORY_END_OFFSET],

		(uint32_t)offset_start);



	/* Writing end of central directory. */

	ret = __archive_write_output(a, end, sizeof(end));

	if (ret != ARCHIVE_OK)

		return (ARCHIVE_FATAL);

	zip->written_bytes += sizeof(end);

	return (ARCHIVE_OK);

}



static int

archive_write_zip_free(struct archive_write *a)

{

	struct zip *zip;

	struct zip_file_header_link *l;



	zip = a->format_data;

	while (zip->central_directory != NULL) {

	   l = zip->central_directory;

	   zip->central_directory = l->next;

	   archive_entry_free(l->entry);

	   free(l);

	}

#ifdef HAVE_ZLIB_H

	free(zip->buf);

#endif

	free(zip);

	a->format_data = NULL;

	return (ARCHIVE_OK);

