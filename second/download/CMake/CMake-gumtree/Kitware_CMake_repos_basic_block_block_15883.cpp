(iso9660->opt.rr) {
		/* Write Rockridge ER(Extensions Reference) */
		ret = write_rr_ER(a);
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}