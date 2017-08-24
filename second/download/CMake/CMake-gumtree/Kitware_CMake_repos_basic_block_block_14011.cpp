{
		if (remaining < 3)
			return (0);
		*p++ = 0xe0 | ((uc >> 12) & 0x0f);
		*p++ = 0x80 | ((uc >> 6) & 0x3f);
		*p++ = 0x80 | (uc & 0x3f);
	}