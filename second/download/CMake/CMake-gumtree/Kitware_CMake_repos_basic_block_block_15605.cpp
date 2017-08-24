(a->archive.archive_format == ARCHIVE_FORMAT_AR_GNU) {
		/*
		 * SVR4/GNU variant use a "/" to mark then end of the filename,
		 * make it possible to have embedded spaces in the filename.
		 * So, the longest filename here (without extension) is
		 * actually 15 bytes.
		 */
		if (strlen(filename) <= 15) {
			strncpy(&buff[AR_name_offset], 
			    filename, strlen(filename));
			buff[AR_name_offset + strlen(filename)] = '/';
		} else {
			/*
			 * For filename longer than 15 bytes, GNU variant
			 * makes use of a string table and instead stores the
			 * offset of the real filename to in the ar_name field.
			 * The string table should have been written before.
			 */
			if (ar->has_strtab <= 0) {
				archive_set_error(&a->archive, EINVAL,
				    "Can't find string table");
				return (ARCHIVE_WARN);
			}

			se = (char *)malloc(strlen(filename) + 3);
			if (se == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate filename buffer");
				return (ARCHIVE_FATAL);
			}

			strncpy(se, filename, strlen(filename));
			strcpy(se + strlen(filename), "/\n");

			ss = strstr(ar->strtab, se);
			free(se);

			if (ss == NULL) {
				archive_set_error(&a->archive, EINVAL,
				    "Invalid string table");
				return (ARCHIVE_WARN);
			}

			/*
			 * GNU variant puts "/" followed by digits into
			 * ar_name field. These digits indicates the real
			 * filename string's offset to the string table.
			 */
			buff[AR_name_offset] = '/';
			if (format_decimal(ss - ar->strtab,
			    buff + AR_name_offset + 1,
			    AR_name_size - 1)) {
				archive_set_error(&a->archive, ERANGE,
				    "string table offset too large");
				return (ARCHIVE_WARN);
			}
		}
	} else if (a->archive.archive_format == ARCHIVE_FORMAT_AR_BSD) {
		/*
		 * BSD variant: for any file name which is more than
		 * 16 chars or contains one or more embedded space(s), the
		 * string "#1/" followed by the ASCII length of the name is
		 * put into the ar_name field. The file size (stored in the
		 * ar_size field) is incremented by the length of the name.
		 * The name is then written immediately following the
		 * archive header.
		 */
		if (strlen(filename) <= 16 && strchr(filename, ' ') == NULL) {
			strncpy(&buff[AR_name_offset], filename, strlen(filename));
			buff[AR_name_offset + strlen(filename)] = ' ';
		}
		else {
			strncpy(buff + AR_name_offset, "#1/", 3);
			if (format_decimal(strlen(filename),
			    buff + AR_name_offset + 3,
			    AR_name_size - 3)) {
				archive_set_error(&a->archive, ERANGE,
				    "File name too long");
				return (ARCHIVE_WARN);
			}
			append_fn = 1;
			size += strlen(filename);
		}
	}