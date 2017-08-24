(a->archive.archive_format == ARCHIVE_FORMAT_AR_BSD) {
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