		return (r);

	/* Update checksum */

	if (*size)

		zip->entry_crc32 = crc32(zip->entry_crc32, *buff,

		    (unsigned)*size);

	/* If we hit the end, swallow any end-of-data marker. */

	if (zip->end_of_entry) {

		/* Check file size, CRC against these values. */

		if (zip->entry->compressed_size !=

		    zip->entry_compressed_bytes_read) {

			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

			    "ZIP compressed data is wrong size "

			    "(read %jd, expected %jd)",

			    (intmax_t)zip->entry_compressed_bytes_read,

			    (intmax_t)zip->entry->compressed_size);

			return (ARCHIVE_WARN);

