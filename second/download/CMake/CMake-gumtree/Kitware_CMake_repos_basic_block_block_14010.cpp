{
		if (remaining < 4)
			return (0);
		*p++ = 0xf0 | ((uc >> 18) & 0x07);
		*p++ = 0x80 | ((uc >> 12) & 0x3f);
		*p++ = 0x80 | ((uc >> 6) & 0x3f);
		*p++ = 0x80 | (uc & 0x3f);
	}