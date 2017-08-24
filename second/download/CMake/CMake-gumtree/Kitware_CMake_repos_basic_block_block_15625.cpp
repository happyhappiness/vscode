do {
		*--p = (char)('0' + (v & 7));
		v >>= 3;
	} while (--s > 0 && v > 0);