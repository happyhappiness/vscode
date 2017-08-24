			return (ARCHIVE_WARN);
		}
		/* Check computed CRC against header */
		if (zip->entry->crc32 != zip->entry_crc32
		    && !zip->ignore_crc32) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "ZIP bad CRC: 0x%lx should be 0x%lx",
