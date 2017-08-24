(sc->flag & SCONV_TO_UTF8) {
		unparse = unicode_to_utf8;
		ts = 1;
	}