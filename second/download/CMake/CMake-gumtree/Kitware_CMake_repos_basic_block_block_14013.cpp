{
		if (remaining < 2)
			return (0);
		*p++ = 0xc0 | ((uc >> 6) & 0x1f);
		*p++ = 0x80 | (uc & 0x3f);
	}