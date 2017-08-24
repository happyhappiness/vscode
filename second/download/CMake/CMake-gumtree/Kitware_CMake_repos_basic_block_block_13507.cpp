(!zip->ignore_crc32
		    && zip_entry->crc32 != zip_entry_central_dir.crc32) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Inconsistent CRC32 values");
			ret = ARCHIVE_WARN;
		}