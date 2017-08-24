{
	int ret, append_fn;
	char buff[60];
	char *ss, *se;
	struct ar_w *ar;
	const char *pathname;
	const char *filename;
	int64_t size;

	append_fn = 0;
	ar = (struct ar_w *)a->format_data;
	ar->is_strtab = 0;
	filename = NULL;
	size = archive_entry_size(entry);


	/*
	 * Reject files with empty name.
	 */
	pathname = archive_entry_pathname(entry);
	if (pathname == NULL || *pathname == '\0') {
		archive_set_error(&a->archive, EINVAL,
		    "Invalid filename");
		return (ARCHIVE_WARN);
	}

	/*
	 * If we are now at the beginning of the archive,
	 * we need first write the ar global header.
	 */
	if (!ar->wrote_global_header) {
		__archive_write_output(a, "!<arch>\n", 8);
		ar->wrote_global_header = 1;
	}

	memset(buff, ' ', 60);
	strncpy(&buff[AR_fmag_offset], "`\n", 2);

	if (strcmp(pathname, "/") == 0 ) {
		/* Entry is archive symbol table in GNU format */
		buff[AR_name_offset] = '/';
		goto stat;
	}
	if (strcmp(pathname, "__.SYMDEF") == 0) {
		/* Entry is archive symbol table in BSD format */
		strncpy(buff + AR_name_offset, "__.SYMDEF", 9);
		goto stat;
	}
	if (strcmp(pathname, "//") == 0) {
		/*
		 * Entry is archive filename table, inform that we should
		 * collect strtab in next _data call.
		 */
		ar->is_strtab = 1;
		buff[AR_name_offset] = buff[AR_name_offset + 1] = '/';
		/*
		 * For archive string table, only ar_size field should
		 * be set.
		 */
		goto size;
	}

	/*
	 * Otherwise, entry is a normal archive member.
	 * Strip leading paths from filenames, if any.
	 */
	if ((filename = ar_basename(pathname)) == NULL) {
		/* Reject filenames with trailing "/" */
		archive_set_error(&a->archive, EINVAL,
		    "Invalid filename");
		return (ARCHIVE_WARN);
	}

	if (a->archive.archive_format == ARCHIVE_FORMAT_AR_GNU) {
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

stat:
	if (format_decimal(archive_entry_mtime(entry), buff + AR_date_offset, AR_date_size)) {
		archive_set_error(&a->archive, ERANGE,
		    "File modification time too large");
		return (ARCHIVE_WARN);
	}
	if (format_decimal(archive_entry_uid(entry), buff + AR_uid_offset, AR_uid_size)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric user ID too large");
		return (ARCHIVE_WARN);
	}
	if (format_decimal(archive_entry_gid(entry), buff + AR_gid_offset, AR_gid_size)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric group ID too large");
		return (ARCHIVE_WARN);
	}
	if (format_octal(archive_entry_mode(entry), buff + AR_mode_offset, AR_mode_size)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric mode too large");
		return (ARCHIVE_WARN);
	}
	/*
	 * Sanity Check: A non-pseudo archive member should always be
	 * a regular file.
	 */
	if (filename != NULL && archive_entry_filetype(entry) != AE_IFREG) {
		archive_set_error(&a->archive, EINVAL,
		    "Regular file required for non-pseudo member");
		return (ARCHIVE_WARN);
	}

size:
	if (format_decimal(size, buff + AR_size_offset, AR_size_size)) {
		archive_set_error(&a->archive, ERANGE,
		    "File size out of range");
		return (ARCHIVE_WARN);
	}

	ret = __archive_write_output(a, buff, 60);
	if (ret != ARCHIVE_OK)
		return (ret);

	ar->entry_bytes_remaining = size;
	ar->entry_padding = ar->entry_bytes_remaining % 2;

	if (append_fn > 0) {
		ret = __archive_write_output(a, filename, strlen(filename));
		if (ret != ARCHIVE_OK)
			return (ret);
		ar->entry_bytes_remaining -= strlen(filename);
	}

	return (ARCHIVE_OK);
}