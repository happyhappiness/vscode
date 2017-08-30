			/* Zip64 extended information extra field. */

			zip_entry->flags |= LA_USED_ZIP64;

			if (zip_entry->uncompressed_size == 0xffffffff) {

				uint64_t t = 0;

				if (datasize < 8

				    || (t = archive_le64dec(p + offset)) > INT64_MAX) {

					archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

					    "Malformed 64-bit uncompressed size");

					return ARCHIVE_FAILED;

				}

				zip_entry->uncompressed_size = t;

				offset += 8;

				datasize -= 8;

			}

			if (zip_entry->compressed_size == 0xffffffff) {

				uint64_t t = 0;

				if (datasize < 8

				    || (t = archive_le64dec(p + offset)) > INT64_MAX) {

					archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

					    "Malformed 64-bit compressed size");

					return ARCHIVE_FAILED;

				}

				zip_entry->compressed_size = t;

				offset += 8;

				datasize -= 8;

			}

			if (zip_entry->local_header_offset == 0xffffffff) {

				uint64_t t = 0;

				if (datasize < 8

				    || (t = archive_le64dec(p + offset)) > INT64_MAX) {

					archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

					    "Malformed 64-bit local header offset");

					return ARCHIVE_FAILED;

				}

				zip_entry->local_header_offset = t;

				offset += 8;

				datasize -= 8;

			}

