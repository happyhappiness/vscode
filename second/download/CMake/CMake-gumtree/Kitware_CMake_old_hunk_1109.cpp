	version = p[4];

	zip_entry->system = p[5];

	zip_entry->flags = archive_le16dec(p + 6);

	zip_entry->compression = archive_le16dec(p + 8);

	zip_entry->mtime = zip_time(p + 10);

	local_crc32 = archive_le32dec(p + 14);

	compressed_size = archive_le32dec(p + 18);

	uncompressed_size = archive_le32dec(p + 22);

	filename_length = archive_le16dec(p + 26);

	extra_length = archive_le16dec(p + 28);



	__archive_read_consume(a, 30);



	if (zip->have_central_directory) {

		/* If we read the central dir entry, we must have size information

		   as well, so ignore the length-at-end flag. */

		zip_entry->flags &= ~ZIP_LENGTH_AT_END;

		/* If we have values from both the local file header

		   and the central directory, warn about mismatches

		   which might indicate a damaged file.  But some

		   writers always put zero in the local header; don't

		   bother warning about that. */

		if (local_crc32 != 0 && local_crc32 != zip_entry->crc32) {

			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

			    "Inconsistent CRC32 values");

			ret = ARCHIVE_WARN;

		}

		if (compressed_size != 0

		    && compressed_size != zip_entry->compressed_size) {

			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

			    "Inconsistent compressed size");

			ret = ARCHIVE_WARN;

		}

		if (uncompressed_size != 0

		    && uncompressed_size != zip_entry->uncompressed_size) {

			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

			    "Inconsistent uncompressed size");

			ret = ARCHIVE_WARN;

		}

