(aes->aes_set & AES_SET_MBS) {
		if (sc == NULL) {
			/* Conversion is unneeded. */
			*p = aes->aes_mbs.s;
			if (length != NULL)
				*length = aes->aes_mbs.length;
			return (0);
		}
		ret = archive_strncpy_l(&(aes->aes_mbs_in_locale),
		    aes->aes_mbs.s, aes->aes_mbs.length, sc);
		*p = aes->aes_mbs_in_locale.s;
		if (length != NULL)
			*length = aes->aes_mbs_in_locale.length;
	} else {
		*p = NULL;
		if (length != NULL)
			*length = 0;
	}