(archive_strlen(&(tar->entry_gname)) > 0) {
		if (archive_entry_copy_gname_l(entry, tar->entry_gname.s,
		    archive_strlen(&(tar->entry_gname)), sconv) != 0) {
			err = set_conversion_failed_error(a, sconv, "Gname");
			if (err == ARCHIVE_FATAL)
				return (err);
			/* Use a converted an original name. */
			archive_entry_copy_gname(entry, tar->entry_gname.s);
		}
	}