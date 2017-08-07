{
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for lzh decompression");
			return (ARCHIVE_FATAL);
		}