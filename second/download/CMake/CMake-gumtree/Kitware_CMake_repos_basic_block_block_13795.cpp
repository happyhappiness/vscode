{
		/*
		 * Normalize UTF-8 and UTF-16BE and convert it directly
		 * to UTF-16 as wchar_t.
		 */
		struct archive_string u16;
		int saved_flag = sc->flag;/* save current flag. */

		if (is_big_endian())
			sc->flag |= SCONV_TO_UTF16BE;
		else
			sc->flag |= SCONV_TO_UTF16LE;

		if (sc->flag & SCONV_FROM_UTF16) {
			/*
			 *  UTF-16BE/LE NFD ===> UTF-16 NFC
			 *  UTF-16BE/LE NFC ===> UTF-16 NFD
			 */
			count = (int)utf16nbytes(s, length);
		} else {
			/*
			 *  UTF-8 NFD ===> UTF-16 NFC
			 *  UTF-8 NFC ===> UTF-16 NFD
			 */
			count = (int)mbsnbytes(s, length);
		}
		u16.s = (char *)dest->s;
		u16.length = dest->length << 1;;
		u16.buffer_length = dest->buffer_length;
		if (sc->flag & SCONV_NORMALIZATION_C)
			ret = archive_string_normalize_C(&u16, s, count, sc);
		else
			ret = archive_string_normalize_D(&u16, s, count, sc);
		dest->s = (wchar_t *)u16.s;
		dest->length = u16.length >> 1;
		dest->buffer_length = u16.buffer_length;
		sc->flag = saved_flag;/* restore the saved flag. */
		return (ret);
	}