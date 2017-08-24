{
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
	}