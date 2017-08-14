static int
archive_write_v7tar_header(struct archive_write *a, struct archive_entry *entry)
{
	char buff[512];
	int ret, ret2;
	struct v7tar *v7tar;
	struct archive_entry *entry_main;
	struct archive_string_conv *sconv;

	v7tar = (struct v7tar *)a->format_data;

	/* Setup default string conversion. */
	if (v7tar->opt_sconv == NULL) {
		if (!v7tar->init_default_conversion) {
			v7tar->sconv_default =
			    archive_string_default_conversion_for_write(
				&(a->archive));
			v7tar->init_default_conversion = 1;
		}
		sconv = v7tar->sconv_default;
	} else
		sconv = v7tar->opt_sconv;

	/* Sanity check. */
	if (archive_entry_pathname(entry) == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Can't record entry in tar file without pathname");
		return (ARCHIVE_FAILED);
	}

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
				    "Can't allocate v7tar data");
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
				    "Can't allocate v7tar data");
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
		    "Can't allocate v7tar data");
		return(ARCHIVE_FATAL);
	}
	if (entry != entry_main)
		entry = entry_main;
	else
		entry_main = NULL;
#else
	entry_main = NULL;
#endif
	ret = format_header_v7tar(a, buff, entry, 1, sconv);
	if (ret < ARCHIVE_WARN) {
		if (entry_main)
			archive_entry_free(entry_main);
		return (ret);
	}
	ret2 = __archive_write_output(a, buff, 512);
	if (ret2 < ARCHIVE_WARN) {
		if (entry_main)
			archive_entry_free(entry_main);
		return (ret2);
	}
	if (ret2 < ret)
		ret = ret2;

	v7tar->entry_bytes_remaining = archive_entry_size(entry);
	v7tar->entry_padding = 0x1ff & (-(int64_t)v7tar->entry_bytes_remaining);
	if (entry_main)
		archive_entry_free(entry_main);
	return (ret);
}