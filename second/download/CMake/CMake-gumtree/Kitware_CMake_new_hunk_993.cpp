				    "Damaged 7-Zip archive");
			return (ARCHIVE_FATAL);
		}

		/*
		 *  Must be kEnd.
		 */
		if ((p = header_bytes(a, 1)) == NULL ||*p != kEnd) {
			archive_set_error(&a->archive, -1,
			    "Malformed 7-Zip archive");
			return (ARCHIVE_FATAL);
		}

		/* Check the Header CRC.*/
		if (check_header_crc && zip->header_crc32 != next_header_crc) {
			archive_set_error(&a->archive, -1,
			    "Malformed 7-Zip archive");
			return (ARCHIVE_FATAL);
