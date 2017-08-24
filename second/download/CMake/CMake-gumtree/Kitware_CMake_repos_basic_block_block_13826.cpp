(*w != L'\0' && len > 0) {
		if (p >= end) {
			as->length = p - as->s;
			as->s[as->length] = '\0';
			/* Re-allocate buffer for MBS. */
			if (archive_string_ensure(as,
			    as->length + len * 2 + 1) == NULL)
				return (-1);
			p = as->s + as->length;
			end = as->s + as->buffer_length - MB_CUR_MAX -1;
		}
#if HAVE_WCRTOMB
		n = wcrtomb(p, *w++, &shift_state);
#else
		n = wctomb(p, *w++);
#endif
		if (n == -1) {
			if (errno == EILSEQ) {
				/* Skip an illegal wide char. */
				*p++ = '?';
				ret_val = -1;
			} else {
				ret_val = -1;
				break;
			}
		} else
			p += n;
		len--;
	}