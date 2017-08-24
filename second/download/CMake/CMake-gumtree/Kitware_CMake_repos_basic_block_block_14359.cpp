{
		memset(a->passphrase, 0, strlen(a->passphrase));
		free(a->passphrase);
		a->passphrase = NULL;
	}