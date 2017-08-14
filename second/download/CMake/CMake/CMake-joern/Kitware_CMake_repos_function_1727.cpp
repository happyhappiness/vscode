static int
get_entry_symlink(struct archive_write *a, struct archive_entry *entry,
    const char **name, size_t *length, struct archive_string_conv *sc)
{
	int r;

	r = archive_entry_symlink_l(entry, name, length, sc);
	if (r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Linkname");
			return (ARCHIVE_FATAL);
		}
		return (ARCHIVE_WARN);
	}
	return (ARCHIVE_OK);
}