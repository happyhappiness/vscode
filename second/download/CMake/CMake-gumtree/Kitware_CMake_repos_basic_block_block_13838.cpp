(sc->flag & SCONV_WIN_CP) {
		add_converter(sc, strncat_in_codepage);
		return;
	}