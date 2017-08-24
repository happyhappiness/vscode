((sc->flag & SCONV_FROM_CHARSET) &&
		    (sc->flag & SCONV_TO_UTF8)) {
			if (sc->flag & SCONV_NORMALIZATION_D)
				add_converter(sc, archive_string_normalize_D);
		}