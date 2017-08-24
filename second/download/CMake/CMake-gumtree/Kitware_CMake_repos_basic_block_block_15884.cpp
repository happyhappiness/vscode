(iso9660->opt.joliet) {
		ret = write_directory_descriptors(a, &(iso9660->joliet));
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}