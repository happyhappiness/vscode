{
		if (c >= 0x80 || map[c] == 0)
		 {
			/* illegal character */
			if (c >= 'a' && c <= 'z') {
				/* convert c from a-z to A-Z */
				c -= 0x20;
			} else
				c = 0x5f;
		}
		*p++ = c;
		l--;
	}