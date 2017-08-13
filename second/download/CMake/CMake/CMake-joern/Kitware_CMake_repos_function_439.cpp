static struct archive_read_passphrase *
new_read_passphrase(struct archive_read *a, const char *passphrase)
{
	struct archive_read_passphrase *p;

	p = malloc(sizeof(*p));
	if (p == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (NULL);
	}
	p->passphrase = strdup(passphrase);
	if (p->passphrase == NULL) {
		free(p);
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (NULL);
	}
	return (p);
}