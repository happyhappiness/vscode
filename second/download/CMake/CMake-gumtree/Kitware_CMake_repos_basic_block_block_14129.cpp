((n = _utf8_to_unicode(&unicode, s, len)) != 0) {
		wchar_t wc;

		if (p >= end) {
			as->length = p - as->s;
			/* Re-allocate buffer for MBS. */
			if (archive_string_ensure(as,
			    as->length + len * 2 + 1) == NULL)
				return (-1);
			p = as->s + as->length;
			end = as->s + as->buffer_length - MB_CUR_MAX -1;
		}

		/*
		 * As libarchive 2.x, translates the UTF-8 characters into
		 * wide-characters in the assumption that WCS is Unicode.
		 */
		if (n < 0) {
			n *= -1;
			wc = L'?';
		} else
			wc = (wchar_t)unicode;

		s += n;
		len -= n;
		/*
		 * Translates the wide-character into the current locale MBS.
		 */
#if HAVE_WCRTOMB
		n = (int)wcrtomb(p, wc, &shift_state);
#else
		n = (int)wctomb(p, wc);
#endif
		if (n == -1)
			return (-1);
		p += n;
	}