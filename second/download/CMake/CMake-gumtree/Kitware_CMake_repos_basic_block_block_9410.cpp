{
		/* Rotate a passphrase list. */
		a->passphrases.candidate--;
		p = remove_passphrases_from_head(a);
		add_passphrase_to_tail(a, p);
		/* Pick a new passphrase candidate up. */
		p = a->passphrases.first;
	}