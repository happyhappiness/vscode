{
	struct cpio *cpio;
	const char *p, *path;
	int pathlength, ret, ret_final;
	int64_t	ino;
	char h[76];
	struct archive_string_conv *sconv;
	struct archive_entry *entry_main;
	size_t len;

	cpio = (struct cpio *)a->format_data;
	ret_final = ARCHIVE_OK;
	sconv = get_sconv(a);

#if defined(_WIN32) && !defined(__CYGWIN__)
	/* Make sure the path separators in pathname, hardlink and symlink
	 * are all slash '/', not the Windows path separator '\'. */
	entry_main = __la_win_entry_in_posix_pathseparator(entry);
	if (entry_main == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate ustar data");
		return(ARCHIVE_FATAL);
	}
	if (entry != entry_main)
		entry = entry_main;
	else
		entry_main = NULL;
#else
	entry_main = NULL;
#endif

	ret = archive_entry_pathname_l(entry, &path, &len, sconv);
	if (ret != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Pathname");
			ret_final = ARCHIVE_FATAL;
			goto exit_write_header;
		}
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate pathname '%s' to %s",
		    archive_entry_pathname(entry),
		    archive_string_conversion_charset_name(sconv));
		ret_final = ARCHIVE_WARN;
	}
	/* Include trailing null. */
	pathlength = (int)len + 1;

	memset(h, 0, sizeof(h));
	format_octal(070707, h + c_magic_offset, c_magic_size);
	format_octal(archive_entry_dev(entry), h + c_dev_offset, c_dev_size);

	ino = synthesize_ino_value(cpio, entry);
	if (ino < 0) {
		archive_set_error(&a->archive, ENOMEM,
		    "No memory for ino translation table");
		ret_final = ARCHIVE_FATAL;
		goto exit_write_header;
	} else if (ino > 0777777) {
		archive_set_error(&a->archive, ERANGE,
		    "Too many files for this cpio format");
		ret_final = ARCHIVE_FATAL;
		goto exit_write_header;
	}
	format_octal(ino & 0777777, h + c_ino_offset, c_ino_size);

	/* TODO: Set ret_final to ARCHIVE_WARN if any of these overflow. */
	format_octal(archive_entry_mode(entry), h + c_mode_offset, c_mode_size);
	format_octal(archive_entry_uid(entry), h + c_uid_offset, c_uid_size);
	format_octal(archive_entry_gid(entry), h + c_gid_offset, c_gid_size);
	format_octal(archive_entry_nlink(entry), h + c_nlink_offset, c_nlink_size);
	if (archive_entry_filetype(entry) == AE_IFBLK
	    || archive_entry_filetype(entry) == AE_IFCHR)
	    format_octal(archive_entry_dev(entry), h + c_rdev_offset, c_rdev_size);
	else
	    format_octal(0, h + c_rdev_offset, c_rdev_size);
	format_octal(archive_entry_mtime(entry), h + c_mtime_offset, c_mtime_size);
	format_octal(pathlength, h + c_namesize_offset, c_namesize_size);

	/* Non-regular files don't store bodies. */
	if (archive_entry_filetype(entry) != AE_IFREG)
		archive_entry_set_size(entry, 0);

	/* Symlinks get the link written as the body of the entry. */
	ret = archive_entry_symlink_l(entry, &p, &len, sconv);
	if (ret != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Linkname");
			ret_final = ARCHIVE_FATAL;
			goto exit_write_header;
		}
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate linkname '%s' to %s",
		    archive_entry_symlink(entry),
		    archive_string_conversion_charset_name(sconv));
		ret_final = ARCHIVE_WARN;
	}
	if (len > 0 && p != NULL  &&  *p != '\0')
		ret = format_octal(strlen(p), h + c_filesize_offset,
		    c_filesize_size);
	else
		ret = format_octal(archive_entry_size(entry),
		    h + c_filesize_offset, c_filesize_size);
	if (ret) {
		archive_set_error(&a->archive, ERANGE,
		    "File is too large for cpio format.");
		ret_final = ARCHIVE_FAILED;
		goto exit_write_header;
	}

	ret = __archive_write_output(a, h, sizeof(h));
	if (ret != ARCHIVE_OK) {
		ret_final = ARCHIVE_FATAL;
		goto exit_write_header;
	}

	ret = __archive_write_output(a, path, pathlength);
	if (ret != ARCHIVE_OK) {
		ret_final = ARCHIVE_FATAL;
		goto exit_write_header;
	}

	cpio->entry_bytes_remaining = archive_entry_size(entry);

	/* Write the symlink now. */
	if (p != NULL  &&  *p != '\0') {
		ret = __archive_write_output(a, p, strlen(p));
		if (ret != ARCHIVE_OK) {
			ret_final = ARCHIVE_FATAL;
			goto exit_write_header;
		}
	}
exit_write_header:
	if (entry_main)
		archive_entry_free(entry_main);
	return (ret_final);
}