	}

	/* CRC check. */
	if (crc32(0, (const unsigned char *)p + 12, 20)
	    != archive_le32dec(p + 8)) {
		archive_set_error(&a->archive, -1, "Header CRC error");
		return (ARCHIVE_FATAL);
	}
