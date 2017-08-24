(p != NULL) {
		struct archive_read_passphrase *np = p->next;

		/* A passphrase should be cleaned. */
		memset(p->passphrase, 0, strlen(p->passphrase));
		free(p->passphrase);
		free(p);
		p = np;
	}