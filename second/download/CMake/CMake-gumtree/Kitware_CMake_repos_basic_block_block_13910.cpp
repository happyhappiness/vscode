{
		int c = (b + a) / 2;
		int r = strcmp(charsets[c].name, cs);
		if (r < 0)
			a = c + 1;
		else if (r > 0)
			b = c;
		else
			return charsets[c].cp;
	}