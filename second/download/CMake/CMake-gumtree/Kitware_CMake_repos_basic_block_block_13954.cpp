(sc != NULL && (sc->flag & SCONV_FROM_UTF16))
			length = utf16nbytes(_p, n);
		else
			length = mbsnbytes(_p, n)