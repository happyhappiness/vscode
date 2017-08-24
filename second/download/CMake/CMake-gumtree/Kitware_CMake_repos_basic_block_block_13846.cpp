(sc->cd != (iconv_t)-1) {
			add_converter(sc, iconv_strncat_in_locale);
			return;
		}