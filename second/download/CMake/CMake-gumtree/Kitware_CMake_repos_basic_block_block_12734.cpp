((err == ARCHIVE_WARN || err == ARCHIVE_OK) &&
	    tar->header_recursion_depth == 0 &&
	    tar->process_mac_extensions) {
		int err2 = read_mac_metadata_blob(a, tar, entry, h, unconsumed);
		if (err2 < err)
			err = err2;
	}