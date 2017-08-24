(namelength == 11 && strncmp((const char *)h, "TRAILER!!!",
	    11) == 0) {
		/* TODO: Store file location of start of block. */
		archive_clear_error(&a->archive);
		return (ARCHIVE_EOF);
	}