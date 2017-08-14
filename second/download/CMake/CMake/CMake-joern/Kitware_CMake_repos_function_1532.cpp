const char *
__archive_write_get_passphrase(struct archive_write *a)
{

	if (a->passphrase != NULL)
		return (a->passphrase);

	if (a->passphrase_callback != NULL) {
		const char *p;
		p = a->passphrase_callback(&a->archive,
		    a->passphrase_client_data);
		if (p != NULL) {
			a->passphrase = strdup(p);
			if (a->passphrase == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate data for passphrase");
				return (NULL);
			}
			return (a->passphrase);
		}
	}
	return (NULL);
}