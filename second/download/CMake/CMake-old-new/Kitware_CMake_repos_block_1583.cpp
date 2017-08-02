{
			err = set_conversion_failed_error(a, sconv, "Gname");
			if (err == ARCHIVE_FATAL)
				return (err);
			/* Use a converted an original name. */
			archive_entry_copy_gname(entry, tar->entry_gname.s);
		}