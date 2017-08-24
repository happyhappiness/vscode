{
			/* Rotate a passphrase list. */
			p = remove_passphrases_from_head(a);
			add_passphrase_to_tail(a, p);
		}