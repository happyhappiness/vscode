{
	unsigned int checksum;
	int i, r, ret;
	size_t copy_length;
	const char *p, *pp;
	int mytartype;

	ret = 0;
	mytartype = -1;
	/*
	 * The "template header" already includes the "v7tar"
	 * signature, various end-of-field markers and other required
	 * elements.
	 */
	memcpy(h, &template_header, 512);

	/*
	 * Because the block is already null-filled, and strings
	 * are allowed to exactly fill their destination (without null),
	 * I use memcpy(dest, src, strlen()) here a lot to copy strings.
	 */
	r = archive_entry_pathname_l(entry, &pp, &copy_length, sconv);
	if (r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Pathname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate pathname '%s' to %s",
		    pp, archive_string_conversion_charset_name(sconv));
		ret = ARCHIVE_WARN;
	}
	if (strict && copy_length < V7TAR_name_size)
		memcpy(h + V7TAR_name_offset, pp, copy_length);
	else if (!strict && copy_length <= V7TAR_name_size)
		memcpy(h + V7TAR_name_offset, pp, copy_length);
	else {
		/* Prefix is too long. */
		archive_set_error(&a->archive, ENAMETOOLONG,
		    "Pathname too long");
		ret = ARCHIVE_FAILED;
	}

	r = archive_entry_hardlink_l(entry, &p, &copy_length, sconv);
	if (r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Linkname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate linkname '%s' to %s",
		    p, archive_string_conversion_charset_name(sconv));
		ret = ARCHIVE_WARN;
	}
	if (copy_length > 0)
		mytartype = '1';
	else {
		r = archive_entry_symlink_l(entry, &p, &copy_length, sconv);
		if (r != 0) {
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for Linkname");
				return (ARCHIVE_FATAL);
			}
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Can't translate linkname '%s' to %s",
			    p, archive_string_conversion_charset_name(sconv));
			ret = ARCHIVE_WARN;
		}
	}
	if (copy_length > 0) {
		if (copy_length >= V7TAR_linkname_size) {
			archive_set_error(&a->archive, ENAMETOOLONG,
			    "Link contents too long");
			ret = ARCHIVE_FAILED;
			copy_length = V7TAR_linkname_size;
		}
		memcpy(h + V7TAR_linkname_offset, p, copy_length);
	}

	if (format_number(archive_entry_mode(entry) & 07777,
	    h + V7TAR_mode_offset, V7TAR_mode_size,
	    V7TAR_mode_max_size, strict)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric mode too large");
		ret = ARCHIVE_FAILED;
	}

	if (format_number(archive_entry_uid(entry),
	    h + V7TAR_uid_offset, V7TAR_uid_size, V7TAR_uid_max_size, strict)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric user ID too large");
		ret = ARCHIVE_FAILED;
	}

	if (format_number(archive_entry_gid(entry),
	    h + V7TAR_gid_offset, V7TAR_gid_size, V7TAR_gid_max_size, strict)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric group ID too large");
		ret = ARCHIVE_FAILED;
	}

	if (format_number(archive_entry_size(entry),
	    h + V7TAR_size_offset, V7TAR_size_size,
	    V7TAR_size_max_size, strict)) {
		archive_set_error(&a->archive, ERANGE,
		    "File size out of range");
		ret = ARCHIVE_FAILED;
	}

	if (format_number(archive_entry_mtime(entry),
	    h + V7TAR_mtime_offset, V7TAR_mtime_size,
	    V7TAR_mtime_max_size, strict)) {
		archive_set_error(&a->archive, ERANGE,
		    "File modification time too large");
		ret = ARCHIVE_FAILED;
	}

	if (mytartype >= 0) {
		h[V7TAR_typeflag_offset] = mytartype;
	} else {
		switch (archive_entry_filetype(entry)) {
		case AE_IFREG: case AE_IFDIR:
			break;
		case AE_IFLNK:
			h[V7TAR_typeflag_offset] = '2';
			break;
		case AE_IFCHR:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive character device");
			return (ARCHIVE_FAILED);
		case AE_IFBLK:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive block device");
			return (ARCHIVE_FAILED);
		case AE_IFIFO:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive fifo");
			return (ARCHIVE_FAILED);
		case AE_IFSOCK:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive socket");
			return (ARCHIVE_FAILED);
		default:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive this (mode=0%lo)",
			    (unsigned long)archive_entry_mode(entry));
			ret = ARCHIVE_FAILED;
		}
	}

	checksum = 0;
	for (i = 0; i < 512; i++)
		checksum += 255 & (unsigned int)h[i];
	format_octal(checksum, h + V7TAR_checksum_offset, 6);
	/* Can't be pre-set in the template. */
	h[V7TAR_checksum_offset + 6] = '\0';
	return (ret);
}