(v >= 0) {
		while (s <= maxsize) {
			if (v < limit)
				return (format_octal(v, p, s));
			s++;
			limit <<= 3;
		}
	}