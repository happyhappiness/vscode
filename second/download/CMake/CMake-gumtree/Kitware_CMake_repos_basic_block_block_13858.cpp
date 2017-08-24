(sc->flag & SCONV_FROM_UTF8) {
			add_converter(sc, archive_string_append_unicode);
			return;
		}