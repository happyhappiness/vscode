do {
		*--p = (char)('0' + (v % 10));
		v /= 10;
	} while (--s > 0 && v > 0);