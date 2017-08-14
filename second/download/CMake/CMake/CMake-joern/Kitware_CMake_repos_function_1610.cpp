static int
header_ustar(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const void *h)
{
	const struct archive_entry_header_ustar	*header;
	struct archive_string *as;
	int err = ARCHIVE_OK, r;

	header = (const struct archive_entry_header_ustar *)h;

	/* Copy name into an internal buffer to ensure null-termination. */
	as = &(tar->entry_pathname);
	if (header->prefix[0]) {
		archive_strncpy(as, header->prefix, sizeof(header->prefix));
		if (as->s[archive_strlen(as) - 1] != '/')
			archive_strappend_char(as, '/');
		archive_strncat(as, header->name, sizeof(header->name));
	} else {
		archive_strncpy(as, header->name, sizeof(header->name));
	}
	if (archive_entry_copy_pathname_l(entry, as->s, archive_strlen(as),
	    tar->sconv) != 0) {
		err = set_conversion_failed_error(a, tar->sconv, "Pathname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}

	/* Handle rest of common fields. */
	r = header_common(a, tar, entry, h);
	if (r == ARCHIVE_FATAL)
		return (r);
	if (r < err)
		err = r;

	/* Handle POSIX ustar fields. */
	if (archive_entry_copy_uname_l(entry,
	    header->uname, sizeof(header->uname), tar->sconv) != 0) {
		err = set_conversion_failed_error(a, tar->sconv, "Uname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}

	if (archive_entry_copy_gname_l(entry,
	    header->gname, sizeof(header->gname), tar->sconv) != 0) {
		err = set_conversion_failed_error(a, tar->sconv, "Gname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}

	/* Parse out device numbers only for char and block specials. */
	if (header->typeflag[0] == '3' || header->typeflag[0] == '4') {
		archive_entry_set_rdevmajor(entry, (dev_t)
		    tar_atol(header->rdevmajor, sizeof(header->rdevmajor)));
		archive_entry_set_rdevminor(entry, (dev_t)
		    tar_atol(header->rdevminor, sizeof(header->rdevminor)));
	}

	tar->entry_padding = 0x1ff & (-tar->entry_bytes_remaining);

	return (err);
}