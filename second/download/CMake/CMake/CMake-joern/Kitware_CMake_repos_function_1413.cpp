static int
archive_write_gnutar_header(struct archive_write *a,
     struct archive_entry *entry)
{
	char buff[512];
	int r, ret, ret2 = ARCHIVE_OK;
	int tartype;
	struct gnutar *gnutar;
	struct archive_string_conv *sconv;
	struct archive_entry *entry_main;

	gnutar = (struct gnutar *)a->format_data;

	/* Setup default string conversion. */
	if (gnutar->opt_sconv == NULL) {
		if (!gnutar->init_default_conversion) {
			gnutar->sconv_default =
			    archive_string_default_conversion_for_write(
				&(a->archive));
			gnutar->init_default_conversion = 1;
		}
		sconv = gnutar->sconv_default;
	} else
		sconv = gnutar->opt_sconv;

	/* Only regular files (not hardlinks) have data. */
	if (archive_entry_hardlink(entry) != NULL ||
	    archive_entry_symlink(entry) != NULL ||
	    !(archive_entry_filetype(entry) == AE_IFREG))
		archive_entry_set_size(entry, 0);

	if (AE_IFDIR == archive_entry_filetype(entry)) {
		const char *p;
		size_t path_length;
		/*
		 * Ensure a trailing '/'.  Modify the entry so
		 * the client sees the change.
		 */
#if defined(_WIN32) && !defined(__CYGWIN__)
		const wchar_t *wp;

		wp = archive_entry_pathname_w(entry);
		if (wp != NULL && wp[wcslen(wp) -1] != L'/') {
			struct archive_wstring ws;

			archive_string_init(&ws);
			path_length = wcslen(wp);
			if (archive_wstring_ensure(&ws,
			    path_length + 2) == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate ustar data");
				archive_wstring_free(&ws);
				return(ARCHIVE_FATAL);
			}
			/* Should we keep '\' ? */
			if (wp[path_length -1] == L'\\')
				path_length--;
			archive_wstrncpy(&ws, wp, path_length);
			archive_wstrappend_wchar(&ws, L'/');
			archive_entry_copy_pathname_w(entry, ws.s);
			archive_wstring_free(&ws);
			p = NULL;
		} else
#endif
			p = archive_entry_pathname(entry);
		/*
		 * On Windows, this is a backup operation just in
		 * case getting WCS failed. On POSIX, this is a
		 * normal operation.
		 */
		if (p != NULL && p[strlen(p) - 1] != '/') {
			struct archive_string as;

			archive_string_init(&as);
			path_length = strlen(p);
			if (archive_string_ensure(&as,
			    path_length + 2) == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate ustar data");
				archive_string_free(&as);
				return(ARCHIVE_FATAL);
			}
#if defined(_WIN32) && !defined(__CYGWIN__)
			/* NOTE: This might break the pathname
			 * if the current code page is CP932 and
			 * the pathname includes a character '\'
			 * as a part of its multibyte pathname. */
			if (p[strlen(p) -1] == '\\')
				path_length--;
			else
#endif
			archive_strncpy(&as, p, path_length);
			archive_strappend_char(&as, '/');
			archive_entry_copy_pathname(entry, as.s);
			archive_string_free(&as);
		}
	}

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
	r = archive_entry_pathname_l(entry, &(gnutar->pathname),
	    &(gnutar->pathname_length), sconv);
	if (r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Pathame");
			ret = ARCHIVE_FATAL;
			goto exit_write_header;
		}
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate pathname '%s' to %s",
		    archive_entry_pathname(entry),
		    archive_string_conversion_charset_name(sconv));
		ret2 = ARCHIVE_WARN;
	}
	r = archive_entry_uname_l(entry, &(gnutar->uname),
	    &(gnutar->uname_length), sconv);
	if (r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Uname");
			ret = ARCHIVE_FATAL;
			goto exit_write_header;
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate uname '%s' to %s",
		    archive_entry_uname(entry),
		    archive_string_conversion_charset_name(sconv));
		ret2 = ARCHIVE_WARN;
	}
	r = archive_entry_gname_l(entry, &(gnutar->gname),
	    &(gnutar->gname_length), sconv);
	if (r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Gname");
			ret = ARCHIVE_FATAL;
			goto exit_write_header;
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate gname '%s' to %s",
		    archive_entry_gname(entry),
		    archive_string_conversion_charset_name(sconv));
		ret2 = ARCHIVE_WARN;
	}

	/* If linkname is longer than 100 chars we need to add a 'K' header. */
	r = archive_entry_hardlink_l(entry, &(gnutar->linkname),
	    &(gnutar->linkname_length), sconv);
	if (r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Linkname");
			ret = ARCHIVE_FATAL;
			goto exit_write_header;
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate linkname '%s' to %s",
		    archive_entry_hardlink(entry),
		    archive_string_conversion_charset_name(sconv));
		ret2 = ARCHIVE_WARN;
	}
	if (gnutar->linkname_length == 0) {
		r = archive_entry_symlink_l(entry, &(gnutar->linkname),
		    &(gnutar->linkname_length), sconv);
		if (r != 0) {
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for Linkname");
				ret = ARCHIVE_FATAL;
				goto exit_write_header;
			}
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Can't translate linkname '%s' to %s",
			    archive_entry_hardlink(entry),
			    archive_string_conversion_charset_name(sconv));
			ret2 = ARCHIVE_WARN;
		}
	}
	if (gnutar->linkname_length > GNUTAR_linkname_size) {
		size_t length = gnutar->linkname_length + 1;
		struct archive_entry *temp = archive_entry_new2(&a->archive);

		/* Uname/gname here don't really matter since no one reads them;
		 * these are the values that GNU tar happens to use on FreeBSD. */
		archive_entry_set_uname(temp, "root");
		archive_entry_set_gname(temp, "wheel");

		archive_entry_set_pathname(temp, "././@LongLink");
		archive_entry_set_size(temp, length);
		ret = archive_format_gnutar_header(a, buff, temp, 'K');
		archive_entry_free(temp);
		if (ret < ARCHIVE_WARN)
			goto exit_write_header;
		ret = __archive_write_output(a, buff, 512);
		if (ret < ARCHIVE_WARN)
			goto exit_write_header;
		/* Write name and trailing null byte. */
		ret = __archive_write_output(a, gnutar->linkname, length);
		if (ret < ARCHIVE_WARN)
			goto exit_write_header;
		/* Pad to 512 bytes */
		ret = __archive_write_nulls(a, 0x1ff & (-(ssize_t)length));
		if (ret < ARCHIVE_WARN)
			goto exit_write_header;
	}

	/* If pathname is longer than 100 chars we need to add an 'L' header. */
	if (gnutar->pathname_length > GNUTAR_name_size) {
		const char *pathname = gnutar->pathname;
		size_t length = gnutar->pathname_length + 1;
		struct archive_entry *temp = archive_entry_new2(&a->archive);

		/* Uname/gname here don't really matter since no one reads them;
		 * these are the values that GNU tar happens to use on FreeBSD. */
		archive_entry_set_uname(temp, "root");
		archive_entry_set_gname(temp, "wheel");

		archive_entry_set_pathname(temp, "././@LongLink");
		archive_entry_set_size(temp, length);
		ret = archive_format_gnutar_header(a, buff, temp, 'L');
		archive_entry_free(temp);
		if (ret < ARCHIVE_WARN)
			goto exit_write_header;
		ret = __archive_write_output(a, buff, 512);
		if(ret < ARCHIVE_WARN)
			goto exit_write_header;
		/* Write pathname + trailing null byte. */
		ret = __archive_write_output(a, pathname, length);
		if(ret < ARCHIVE_WARN)
			goto exit_write_header;
		/* Pad to multiple of 512 bytes. */
		ret = __archive_write_nulls(a, 0x1ff & (-(ssize_t)length));
		if (ret < ARCHIVE_WARN)
			goto exit_write_header;
	}

	if (archive_entry_hardlink(entry) != NULL) {
		tartype = '1';
	} else
		switch (archive_entry_filetype(entry)) {
		case AE_IFREG: tartype = '0' ; break;
		case AE_IFLNK: tartype = '2' ; break;
		case AE_IFCHR: tartype = '3' ; break;
		case AE_IFBLK: tartype = '4' ; break;
		case AE_IFDIR: tartype = '5' ; break;
		case AE_IFIFO: tartype = '6' ; break;
		case AE_IFSOCK:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive socket");
			ret = ARCHIVE_FAILED;
			goto exit_write_header;
		default:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive this (mode=0%lo)",
			    (unsigned long)archive_entry_mode(entry));
			ret = ARCHIVE_FAILED;
			goto exit_write_header;
		}

	ret = archive_format_gnutar_header(a, buff, entry, tartype);
	if (ret < ARCHIVE_WARN)
		goto exit_write_header;
	if (ret2 < ret)
		ret = ret2;
	ret2 = __archive_write_output(a, buff, 512);
	if (ret2 < ARCHIVE_WARN) {
		ret = ret2;
		goto exit_write_header;
	}
	if (ret2 < ret)
		ret = ret2;

	gnutar->entry_bytes_remaining = archive_entry_size(entry);
	gnutar->entry_padding = 0x1ff & (-(int64_t)gnutar->entry_bytes_remaining);
exit_write_header:
	if (entry_main)
		archive_entry_free(entry_main);
	return (ret);
}