(archive_entry_copy_pathname_l(entry,
	    header->name, sizeof(header->name), tar->sconv) != 0) {
		err = set_conversion_failed_error(a, tar->sconv, "Pathname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}