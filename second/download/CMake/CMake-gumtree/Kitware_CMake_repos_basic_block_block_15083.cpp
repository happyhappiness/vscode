{
		h = (h << 4) + *p++;
		if ((g = h & 0xF0000000) != 0) {
			h ^= g >> 24;
			h &= 0x0FFFFFFF;
		}
	}