			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Pathname is too long");
		}

		r = archive_entry_copy_pathname_l(entry,
