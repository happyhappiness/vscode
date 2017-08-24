{
			uint64_t compressed, uncompressed;
			zip->entry->crc32 = archive_le32dec(p);
			compressed = archive_le64dec(p + 4);
			uncompressed = archive_le64dec(p + 12);
			if (compressed > INT64_MAX || uncompressed > INT64_MAX) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Overflow of 64-bit file sizes");
				return ARCHIVE_FAILED;
			}
			zip->entry->compressed_size = compressed;
			zip->entry->uncompressed_size = uncompressed;
			zip->unconsumed += 20;
		}