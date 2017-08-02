archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "ZIP uncompressed data is wrong size "
			    "(read %jd, expected %jd)\n",
			    (intmax_t)zip->entry_uncompressed_bytes_read,
			    (intmax_t)zip->entry->uncompressed_size)