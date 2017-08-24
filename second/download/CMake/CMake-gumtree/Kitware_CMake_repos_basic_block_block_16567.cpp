(zisofs->block_pointers == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for zisofs decompression");
			return (ARCHIVE_FATAL);
		}