(*s) {
		char c = *s++;
		if (c >= 'a' && c <= 'z')
			c -= 'a' - 'A';
		*p++ = c;
	}