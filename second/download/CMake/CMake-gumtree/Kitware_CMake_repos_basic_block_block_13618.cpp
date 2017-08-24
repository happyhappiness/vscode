{
		const char *passphrase;

		passphrase = __archive_read_next_passphrase(a);
		if (passphrase == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    (retry > 0)?
				"Incorrect passphrase":
				"Passphrase required for this entry");
			return (ARCHIVE_FAILED);
		}
		memset(derived_key, 0, sizeof(derived_key));
		r = archive_pbkdf2_sha1(passphrase, strlen(passphrase),
		    p, salt_len, 1000, derived_key, key_len * 2 + 2);
		if (r != 0) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Decryption is unsupported due to lack of "
			    "crypto library");
			return (ARCHIVE_FAILED);
		}

		/* Check password verification value. */
		pv = ((const uint8_t *)p) + salt_len;
		if (derived_key[key_len * 2] == pv[0] &&
		    derived_key[key_len * 2 + 1] == pv[1])
			break;/* The passphrase is OK. */
		if (retry > 10000) {
			/* Avoid infinity loop. */
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Too many incorrect passphrases");
			return (ARCHIVE_FAILED);
		}
	}