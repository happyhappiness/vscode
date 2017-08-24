(archive_strlen(&(tar->entry_uname)) > 0) {
		if (archive_entry_copy_uname_l(entry, tar->entry_uname.s,
		    archive_strlen(&(tar->entry_uname)), sconv) != 0) {
			err = set_conversion_failed_error(a, sconv, "Uname");
			if (err == ARCHIVE_FATAL)
				return (err);
			/* Use a converted an original name. */
			archive_entry_copy_uname(entry, tar->entry_uname.s);
		}
	}