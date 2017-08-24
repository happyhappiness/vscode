{
		count = (int)utf16nbytes(s, length);
		count >>= 1; /* to be WCS length */
		/* Allocate memory for WCS. */
		if (NULL == archive_wstring_ensure(dest,
		    dest->length + count + 1))
			return (-1);
		wmemcpy(dest->s + dest->length, (const wchar_t *)s, count);
		if ((sc->flag & SCONV_FROM_UTF16BE) && !is_big_endian()) {
			uint16_t *u16 = (uint16_t *)(dest->s + dest->length);
			int b;
			for (b = 0; b < count; b++) {
				uint16_t val = archive_le16dec(u16+b);
				archive_be16enc(u16+b, val);
			}
		} else if ((sc->flag & SCONV_FROM_UTF16LE) && is_big_endian()) {
			uint16_t *u16 = (uint16_t *)(dest->s + dest->length);
			int b;
			for (b = 0; b < count; b++) {
				uint16_t val = archive_be16dec(u16+b);
				archive_le16enc(u16+b, val);
			}
		}
	}