(aes->aes_set & AES_SET_WCS) {
		archive_string_empty(&(aes->aes_mbs));
		r = archive_string_append_from_wcs(&(aes->aes_mbs),
		    aes->aes_wcs.s, aes->aes_wcs.length);
		*p = aes->aes_mbs.s;
		if (r == 0) {
			aes->aes_set |= AES_SET_MBS;
			return (ret);
		} else
			ret = -1;
	}