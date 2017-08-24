(off < iso9660->wbuff_offset) {
		/*
		 * Write out waiting data.
		 */
		if (used > 0) {
			if (wb_write_out(a) != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
		}
		lseek(iso9660->temp_fd, off, SEEK_SET);
		iso9660->wbuff_offset = off;
		iso9660->wbuff_remaining = sizeof(iso9660->wbuff);
	} else if (off <= iso9660->wbuff_tail) {
		iso9660->wbuff_remaining = (size_t)
		    (sizeof(iso9660->wbuff) - (off - iso9660->wbuff_offset));
	} else {
		ext_bytes = off - iso9660->wbuff_tail;
		iso9660->wbuff_remaining = (size_t)(sizeof(iso9660->wbuff)
		   - (iso9660->wbuff_tail - iso9660->wbuff_offset));
		while (ext_bytes >= (int64_t)iso9660->wbuff_remaining) {
			if (write_null(a, (size_t)iso9660->wbuff_remaining)
			    != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			ext_bytes -= iso9660->wbuff_remaining;
		}
		if (ext_bytes > 0) {
			if (write_null(a, (size_t)ext_bytes) != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
		}
	}