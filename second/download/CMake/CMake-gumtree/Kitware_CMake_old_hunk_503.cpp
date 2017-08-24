		if (entry_size == 0) {
			archive_set_error(&a->archive, EINVAL,
			    "Invalid string table");
			return (ARCHIVE_WARN);
		}
		if (ar->strtab != NULL) {
			archive_set_error(&a->archive, EINVAL,
			    "More than one string tables exist");
			return (ARCHIVE_WARN);
		}

		/* Read the filename table into memory. */
