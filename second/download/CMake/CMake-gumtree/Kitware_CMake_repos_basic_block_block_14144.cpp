{
		/*
		 * "C" locale special process.
		 */
		u16 = _p;
		ll = 0;
		for (b = 0; b < bytes; b += 2) {
			uint16_t val;
			if (be)
				val = archive_be16dec(u16+b);
			else
				val = archive_le16dec(u16+b);
			if (val > 255) {
				*mbs++ = '?';
				ret = -1;
			} else
				*mbs++ = (char)(val&0xff);
			ll++;
		}
		as->length += ll;
		as->s[as->length] = '\0';
		return (ret);
	}