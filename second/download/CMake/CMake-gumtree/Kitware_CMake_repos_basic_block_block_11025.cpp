(strcmp(filename, "//") == 0) {
		/* This must come before any call to _read_ahead. */
		ar_parse_common_header(ar, entry, h);
		archive_entry_copy_pathname(entry, filename);
		archive_entry_set_filetype(entry, AE_IFREG);
		/* Get the size of the filename table. */
		number = ar_atol10(h + AR_size_offset, AR_size_size);
		if (number > SIZE_MAX || number > 1024 * 1024 * 1024) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Filename table too large");
			return (ARCHIVE_FATAL);
		}
		entry_size = (size_t)number;
		if (entry_size == 0) {
			archive_set_error(&a->archive, EINVAL,
			    "Invalid string table");
			return (ARCHIVE_FATAL);
		}
		if (ar->strtab != NULL) {
			archive_set_error(&a->archive, EINVAL,
			    "More than one string tables exist");
			return (ARCHIVE_FATAL);
		}

		/* Read the filename table into memory. */
		st = malloc(entry_size);
		if (st == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate filename table buffer");
			return (ARCHIVE_FATAL);
		}
		ar->strtab = st;
		ar->strtab_size = entry_size;

		if (*unconsumed) {
			__archive_read_consume(a, *unconsumed);
			*unconsumed = 0;
		}

		if ((b = __archive_read_ahead(a, entry_size, NULL)) == NULL)
			return (ARCHIVE_FATAL);
		memcpy(st, b, entry_size);
		__archive_read_consume(a, entry_size);
		/* All contents are consumed. */
		ar->entry_bytes_remaining = 0;
		archive_entry_set_size(entry, ar->entry_bytes_remaining);

		/* Parse the filename table. */
		return (ar_parse_gnu_filename_table(a));
	}