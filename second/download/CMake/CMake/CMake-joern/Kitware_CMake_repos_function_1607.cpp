static int
header_old_tar(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const void *h)
{
	const struct archive_entry_header_ustar	*header;
	int err = ARCHIVE_OK, err2;

	/* Copy filename over (to ensure null termination). */
	header = (const struct archive_entry_header_ustar *)h;
	if (archive_entry_copy_pathname_l(entry,
	    header->name, sizeof(header->name), tar->sconv) != 0) {
		err = set_conversion_failed_error(a, tar->sconv, "Pathname");
		if (err == ARCHIVE_FATAL)
			return (err);
	}

	/* Grab rest of common fields */
	err2 = header_common(a, tar, entry, h);
	if (err > err2)
		err = err2;

	tar->entry_padding = 0x1ff & (-tar->entry_bytes_remaining);
	return (err);
}