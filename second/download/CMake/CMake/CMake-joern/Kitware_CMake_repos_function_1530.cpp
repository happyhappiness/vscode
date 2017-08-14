int
archive_write_set_passphrase(struct archive *_a, const char *p)
{
	struct archive_write *a = (struct archive_write *)_a;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC, ARCHIVE_STATE_NEW,
		"archive_write_set_passphrase");

	if (p == NULL || p[0] == '\0') {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Empty passphrase is unacceptable");
		return (ARCHIVE_FAILED);
	}
	free(a->passphrase);
	a->passphrase = strdup(p);
	if (a->passphrase == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate data for passphrase");
		return (ARCHIVE_FATAL);
	}
	return (ARCHIVE_OK);
}