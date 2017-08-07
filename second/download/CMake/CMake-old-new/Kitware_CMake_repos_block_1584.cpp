{
			err = set_conversion_failed_error(a, sconv, "Linkname");
			if (err == ARCHIVE_FATAL)
				return (err);
			/* Use a converted an original name. */
			archive_entry_copy_link(entry, tar->entry_linkpath.s);
		}