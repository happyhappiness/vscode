(passphrase != NULL) {
			p = new_read_passphrase(a, passphrase);
			if (p == NULL)
				return (NULL);
			insert_passphrase_to_head(a, p);
			a->passphrases.candidate = 1;
		}