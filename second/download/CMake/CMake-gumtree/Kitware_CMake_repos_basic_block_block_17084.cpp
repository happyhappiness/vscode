{
		v = (((int)s[0] << 16) & 0xff0000)
		    | (((int)s[1] << 8) & 0xff00)
		    | (((int)s[2]) & 0x00ff);
		s += 3;
		len -= 3;
		*d++ = digits[(v >> 18) & 0x3f];
		*d++ = digits[(v >> 12) & 0x3f];
		*d++ = digits[(v >> 6) & 0x3f];
		*d++ = digits[(v) & 0x3f];
	}