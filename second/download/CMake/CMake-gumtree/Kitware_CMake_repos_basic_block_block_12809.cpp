(archive_entry_copy_uname_l(entry,
	    header->uname, sizeof(header->uname), tar->sconv) != 0) {
		err = set_conversion_failed_error(a, tar->sconv, "Uname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}