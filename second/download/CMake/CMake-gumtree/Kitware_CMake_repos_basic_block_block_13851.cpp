(sc->flag & SCONV_TO_UTF8) {
			/*
			 * If the current locale is UTF-8, we can translate
			 * a UTF-16BE/LE string into a UTF-8 string directly.
			 */
			if (!(sc->flag &
			    (SCONV_NORMALIZATION_D |SCONV_NORMALIZATION_C)))
				add_converter(sc,
				    archive_string_append_unicode);
			return;
		}