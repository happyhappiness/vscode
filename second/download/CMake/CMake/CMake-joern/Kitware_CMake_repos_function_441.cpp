int
archive_read_add_passphrase(struct archive *_a, const char *passphrase)
{
	struct archive_read *a = (struct archive_read *)_a;
	struct archive_read_passphrase *p;

	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,
		"archive_read_add_passphrase");

	if (passphrase == NULL || passphrase[0] == '\0') {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Empty passphrase is unacceptable");
		return (ARCHIVE_FAILED);
	}

	p = new_read_passphrase(a, passphrase);
	if (p == NULL)
		return (ARCHIVE_FATAL);
	add_passphrase_to_tail(a, p);

	return (ARCHIVE_OK);
}