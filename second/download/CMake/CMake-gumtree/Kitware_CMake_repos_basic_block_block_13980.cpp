(sc->flag & SCONV_TO_UTF8) {
				if (archive_string_append(as, utf8_replacement_char, sizeof(utf8_replacement_char)) == NULL) {
					__archive_errx(1, "Out of memory");
				}
			} else {
				archive_strappend_char(as, '?');
			}