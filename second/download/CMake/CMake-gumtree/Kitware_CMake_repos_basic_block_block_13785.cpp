(sc->flag & SCONV_FROM_CHARSET) {
			/* Do not trust the length which comes from
			 * an archive file. */
			length = mbsnbytes(s, length);
			mbflag = 0;
		}