
		/* Parse the size of the name, adjust the file size. */
		number = ar_atol10(h + AR_name_offset + 3, AR_name_size - 3);
		bsd_name_length = (size_t)number;
		/* Guard against the filename + trailing NUL
		 * overflowing a size_t and against the filename size
		 * being larger than the entire entry. */
		if (number > (uint64_t)(bsd_name_length + 1)
		    || (int64_t)bsd_name_length > ar->entry_bytes_remaining) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Bad input file size");
			return (ARCHIVE_FATAL);
		}
		ar->entry_bytes_remaining -= bsd_name_length;
		/* Adjust file size reported to client. */
		archive_entry_set_size(entry, ar->entry_bytes_remaining);