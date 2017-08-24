(sc->cd != (iconv_t)-1) {
		add_converter(sc, iconv_strncat_in_locale);
		/*
		 * iconv generally does not support UTF-8-MAC and so
		 * we have to the output of iconv from NFC to NFD if
		 * need.
		 */
		if ((sc->flag & SCONV_FROM_CHARSET) &&
		    (sc->flag & SCONV_TO_UTF8)) {
			if (sc->flag & SCONV_NORMALIZATION_D)
				add_converter(sc, archive_string_normalize_D);
		}
		return;
	}