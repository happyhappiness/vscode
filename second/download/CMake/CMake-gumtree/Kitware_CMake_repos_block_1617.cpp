{
			err = set_conversion_failed_error(a, sconv, "Pathname");
			if (err == ARCHIVE_FATAL)
				return (err);
			/* Use a converted an original name. */
			archive_entry_copy_pathname(entry, as->s);
		}