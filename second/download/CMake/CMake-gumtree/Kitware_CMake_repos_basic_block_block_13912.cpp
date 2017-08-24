{
		char c = *charset++;
		if (c >= 'a' && c <= 'z')
			c -= 'a' - 'A';
		*p++ = c;
	}