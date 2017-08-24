{
	int err;

	err = read_body_to_string(a, tar, &(tar->longlink), h, unconsumed);
	if (err != ARCHIVE_OK)
		return (err);
	err = tar_read_header(a, tar, entry, unconsumed);
	if ((err != ARCHIVE_OK) && (err != ARCHIVE_WARN))
		return (err);
	/* Set symlink if symlink already set, else hardlink. */
	archive_entry_copy_link(entry, tar->longlink.s);
	return (ARCHIVE_OK);
}