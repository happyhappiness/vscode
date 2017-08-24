(n < 0) {
			if (n == -3 && IS_SURROGATE_PAIR_LA(uc)) {
				/* Current byte sequence may be CESU-8. */
				n = cesu8_to_unicode(&uc, s, len);
			}
			if (n < 0) {
				ret = -1;
				n *= -1;/* Use a replaced unicode character. */
			}

			/* Rebuild UTF-8 byte sequence. */
			while ((w = unicode_to_utf8(p, endp - p, uc)) == 0) {
				as->length = p - as->s;
				if (archive_string_ensure(as,
				    as->buffer_length + len + 1) == NULL)
					return (-1);
				p = as->s + as->length;
				endp = as->s + as->buffer_length -1;
			}
			p += w;
			s += n;
			len -= n;
		}