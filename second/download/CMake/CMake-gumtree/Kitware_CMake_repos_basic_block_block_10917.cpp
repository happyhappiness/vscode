(zip->uncompressed_buffer == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for 7-Zip decompression");
			return (ARCHIVE_FATAL);
		}