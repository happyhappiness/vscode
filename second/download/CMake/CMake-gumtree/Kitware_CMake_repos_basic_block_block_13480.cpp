(datasize < 8
				    || (t = archive_le64dec(p + offset)) > INT64_MAX) {
					archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
					    "Malformed 64-bit local header offset");
					return ARCHIVE_FAILED;
				}