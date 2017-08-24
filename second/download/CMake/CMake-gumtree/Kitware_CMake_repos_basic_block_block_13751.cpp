(offset != zip->entry->local_header_offset) {
		__archive_read_seek(a, zip->entry->local_header_offset,
		    SEEK_SET);
	}