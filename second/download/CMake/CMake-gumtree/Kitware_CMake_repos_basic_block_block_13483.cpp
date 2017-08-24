{
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