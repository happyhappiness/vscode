((p = header_bytes(a, 1)) == NULL ||*p != kEnd) {
			archive_set_error(&a->archive, -1,
			    "Malformed 7-Zip archive");
			return (ARCHIVE_FATAL);
		}