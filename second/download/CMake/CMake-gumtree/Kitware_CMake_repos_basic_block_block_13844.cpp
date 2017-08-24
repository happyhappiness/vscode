((sc->flag & (SCONV_BEST_EFFORT | SCONV_FROM_UTF16BE))
		    == (SCONV_BEST_EFFORT | SCONV_FROM_UTF16BE))
			add_converter(sc, best_effort_strncat_from_utf16be);
		else if ((sc->flag & (SCONV_BEST_EFFORT | SCONV_FROM_UTF16LE))
		    == (SCONV_BEST_EFFORT | SCONV_FROM_UTF16LE))
			add_converter(sc, best_effort_strncat_from_utf16le);
		else
			/* Make sure we have no converter. */
			sc->nconverter = 0