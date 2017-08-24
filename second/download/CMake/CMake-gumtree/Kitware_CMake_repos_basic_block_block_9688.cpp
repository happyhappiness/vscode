(bytes == 0 && !empty_sparse_region) {
		/* Get EOF */
		t->entry_eof = 1;
		r = ARCHIVE_EOF;
		goto abort_read_data;
	}