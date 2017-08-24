(iso9660->opt.joliet) {
		ret = write_VD(a, &(iso9660->joliet));
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}