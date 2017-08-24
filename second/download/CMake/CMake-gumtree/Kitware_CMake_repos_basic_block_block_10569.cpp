((zip->entry->flg & CRC32_IS_SET) &&
			zip->si.ss.digests[zip->entry->ssIndex] !=
		    zip->entry_crc32) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "7-Zip bad CRC: 0x%lx should be 0x%lx",
			    (unsigned long)zip->entry_crc32,
			    (unsigned long)zip->si.ss.digests[
			    		zip->entry->ssIndex]);
			ret = ARCHIVE_WARN;
		}