(0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END)) {
	    zip->entry_bytes_remaining -= ENC_HEADER_SIZE;
	}