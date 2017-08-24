{
		/* Parse the time, owner, mode, size fields. */
		/* This must occur before _read_ahead is called again. */
		ar_parse_common_header(ar, entry, h);

		/* Parse the size of the name, adjust the file size. */
		number = ar_atol10(h + AR_name_offset + 3, AR_name_size - 3);
		/* Sanity check the filename length:
		 *   = Must be <= SIZE_MAX - 1
		 *   = Must be <= 1MB
		 *   = Cannot be bigger than the entire entry
		 */
		if (number > SIZE_MAX - 1
		    || number > 1024 * 1024
		    || (int64_t)number > ar->entry_bytes_remaining) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Bad input file size");
			return (ARCHIVE_FATAL);
		}
		bsd_name_length = (size_t)number;
		ar->entry_bytes_remaining -= bsd_name_length;
		/* Adjust file size reported to client. */
		archive_entry_set_size(entry, ar->entry_bytes_remaining);

		if (*unconsumed) {
			__archive_read_consume(a, *unconsumed);
			*unconsumed = 0;
		}

		/* Read the long name into memory. */
		if ((b = __archive_read_ahead(a, bsd_name_length, NULL)) == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Truncated input file");
			return (ARCHIVE_FATAL);
		}
		/* Store it in the entry. */
		p = (char *)malloc(bsd_name_length + 1);
		if (p == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate fname buffer");
			return (ARCHIVE_FATAL);
		}
		strncpy(p, b, bsd_name_length);
		p[bsd_name_length] = '\0';

		__archive_read_consume(a, bsd_name_length);

		archive_entry_copy_pathname(entry, p);
		free(p);
		return (ARCHIVE_OK);
	}