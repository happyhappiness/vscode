{
		/*
		 * Convert characters from a specified charset to
		 * the current locale charset.
		 */
		sc->to_cp = current_codepage;
		sc->from_cp = make_codepage_from_charset(fc);
#if defined(_WIN32) && !defined(__CYGWIN__)
		if (IsValidCodePage(sc->from_cp))
			flag |= SCONV_WIN_CP;
#endif
	}