{
		if (used > 0 &&
		    write_to_temp(a, iso9660->wbuff, (size_t)used) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		iso9660->wbuff_offset = iso9660->wbuff_written;
		lseek(iso9660->temp_fd, iso9660->wbuff_offset, SEEK_SET);
		iso9660->wbuff_remaining = sizeof(iso9660->wbuff);
		used = 0;
	}