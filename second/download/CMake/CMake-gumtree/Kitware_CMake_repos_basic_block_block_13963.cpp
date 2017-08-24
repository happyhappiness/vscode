(sc->flag & (SCONV_TO_UTF8 | SCONV_TO_UTF16)) {
				size_t rbytes;
				if (sc->flag & SCONV_TO_UTF8)
					rbytes = sizeof(utf8_replacement_char);
				else
					rbytes = 2;

				if (avail < rbytes) {
					as->length = outp - as->s;
					bs = as->buffer_length +
					    (remaining * to_size) + rbytes;
					if (NULL ==
					    archive_string_ensure(as, bs))
						return (-1);
					outp = as->s + as->length;
					avail = as->buffer_length
					    - as->length - to_size;
				}
				if (sc->flag & SCONV_TO_UTF8)
					memcpy(outp, utf8_replacement_char, sizeof(utf8_replacement_char));
				else if (sc->flag & SCONV_TO_UTF16BE)
					archive_be16enc(outp, UNICODE_R_CHAR);
				else
					archive_le16enc(outp, UNICODE_R_CHAR);
				outp += rbytes;
				avail -= rbytes;
			} else {
				/* Skip the illegal input bytes. */
				*outp++ = '?';
				avail--;
			}