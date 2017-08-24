(sc->from_cp == CP_C_LOCALE) {
		/*
		 * "C" locale special process.
		 */
		count = 0;
		while (count < length && *s) {
			if (bigendian)
				archive_be16enc(u16, *s);
			else
				archive_le16enc(u16, *s);
			u16 += 2;
			s++;
			count++;
		}
		as16->length += count << 1;
		as16->s[as16->length] = 0;
		as16->s[as16->length+1] = 0;
		return (0);
	}