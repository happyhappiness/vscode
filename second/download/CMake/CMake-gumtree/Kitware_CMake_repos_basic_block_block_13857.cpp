(sc->flag & SCONV_WIN_CP) {
			if (sc->flag & SCONV_TO_UTF16BE)
				add_converter(sc, win_strncat_to_utf16be);
			else
				add_converter(sc, win_strncat_to_utf16le);
			return;
		}