{
			if (zip->entry->flags & LA_USED_ZIP64) {
				uint64_t compressed, uncompressed;
				zip->entry->crc32 = archive_le32dec(p + 4);
				compressed = archive_le64dec(p + 8);
				uncompressed = archive_le64dec(p + 16);
				if (compressed > INT64_MAX || uncompressed > INT64_MAX) {
					archive_set_error(&a->archive,
					    ARCHIVE_ERRNO_FILE_FORMAT,
					    "Overflow of 64-bit file sizes");
					return ARCHIVE_FAILED;
				}
				zip->entry->compressed_size = compressed;
				zip->entry->uncompressed_size = uncompressed;
				zip->unconsumed = 24;
			} else {
				zip->entry->crc32 = archive_le32dec(p + 4);
				zip->entry->compressed_size =
					archive_le32dec(p + 8);
				zip->entry->uncompressed_size =
					archive_le32dec(p + 12);
				zip->unconsumed = 16;
			}
			if (zip->hctx_valid) {
				r = check_authentication_code(a, buff);
				if (r != ARCHIVE_OK)
					return (r);
			}
			zip->end_of_entry = 1;
			return (ARCHIVE_OK);
		}