
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