{
		struct iso9660 *iso9660 = (struct iso9660 *)a->format_data;
		xs = s % LOGICAL_BLOCK_SIZE;
		iso9660->wbuff_offset += s - xs;
		if (write_to_temp(a, buff, s - xs) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		if (xs == 0)
			return (ARCHIVE_OK);
		xp += s - xs;
	}