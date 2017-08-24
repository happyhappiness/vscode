(sc->flag & SCONV_NORMALIZATION_D)
			add_converter(sc,archive_string_normalize_D);
		else if (sc->flag & SCONV_NORMALIZATION_C)
			add_converter(sc, archive_string_normalize_C)