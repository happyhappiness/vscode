{
	int64_t size;
	const void *data;
	const char *p, *name;
	const wchar_t *wp, *wname;

	(void)h; /* UNUSED */

	wname = wp = archive_entry_pathname_w(entry);
	if (wp != NULL) {
		/* Find the last path element. */
		for (; *wp != L'\0'; ++wp) {
			if (wp[0] == '/' && wp[1] != L'\0')
				wname = wp + 1;
		}
		/*
		 * If last path element starts with "._", then
		 * this is a Mac extension.
		 */
		if (wname[0] != L'.' || wname[1] != L'_' || wname[2] == L'\0')
			return ARCHIVE_OK;
	} else {
		/* Find the last path element. */
		name = p = archive_entry_pathname(entry);
		if (p == NULL)
			return (ARCHIVE_FAILED);
		for (; *p != '\0'; ++p) {
			if (p[0] == '/' && p[1] != '\0')
				name = p + 1;
		}
		/*
		 * If last path element starts with "._", then
		 * this is a Mac extension.
		 */
		if (name[0] != '.' || name[1] != '_' || name[2] == '\0')
			return ARCHIVE_OK;
	}

 	/* Read the body as a Mac OS metadata blob. */
	size = archive_entry_size(entry);

	/*
	 * TODO: Look beyond the body here to peek at the next header.
	 * If it's a regular header (not an extension header)
	 * that has the wrong name, just return the current
	 * entry as-is, without consuming the body here.
	 * That would reduce the risk of us mis-identifying
	 * an ordinary file that just happened to have
	 * a name starting with "._".
	 *
	 * Q: Is the above idea really possible?  Even
	 * when there are GNU or pax extension entries?
	 */
	data = __archive_read_ahead(a, (size_t)size, NULL);
	if (data == NULL) {
		*unconsumed = 0;
		return (ARCHIVE_FATAL);
	}
	archive_entry_copy_mac_metadata(entry, data, (size_t)size);
	*unconsumed = (size_t)((size + 511) & ~ 511);
	tar_flush_unconsumed(a, unconsumed);
	return (tar_read_header(a, tar, entry, unconsumed));
}