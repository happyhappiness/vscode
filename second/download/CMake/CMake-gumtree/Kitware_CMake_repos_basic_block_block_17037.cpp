(pax->opt_binary)
		sconv = NULL;/* Binary mode. */
	else {
		/* Header encoding is UTF-8. */
		if (pax->sconv_utf8 == NULL) {
			/* Initialize the string conversion object
			 * we must need */
			pax->sconv_utf8 = archive_string_conversion_to_charset(
			    &(a->archive), "UTF-8", 1);
			if (pax->sconv_utf8 == NULL)
				/* Couldn't allocate memory */
				return (ARCHIVE_FAILED);
		}
		sconv = pax->sconv_utf8;
	}