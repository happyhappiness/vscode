{
		memmove(h, p, len - s);
		p = h + len - s;
		while (s-- > 0)
			*p++ = ' ';
		return (0);
	}