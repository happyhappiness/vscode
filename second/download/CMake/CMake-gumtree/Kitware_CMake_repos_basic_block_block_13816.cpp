{
		uint16_t *u16;

		if (NULL ==
		    archive_string_ensure(as, as->length + len * 2 + 2))
			return (-1);
		u16 = (uint16_t *)(as->s + as->length);
		count = 0;
		defchar_used = 0;
		if (sc->flag & SCONV_TO_UTF16BE) {
			while (count < (int)len && *ws) {
				archive_be16enc(u16+count, *ws);
				ws++;
				count++;
			}
		} else {
			while (count < (int)len && *ws) {
				archive_le16enc(u16+count, *ws);
				ws++;
				count++;
			}
		}
		count <<= 1; /* to be byte size */
	}