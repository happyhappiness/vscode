{
		/* This case is that all candidates failed to decrypt. */
		a->passphrases.candidate = 0;
		if (a->passphrases.first->next != NULL) {
			/* Rotate a passphrase list. */
			p = remove_passphrases_from_head(a);
			add_passphrase_to_tail(a, p);
		}
		p = NULL;
	}