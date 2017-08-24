(i = 0; i < num; i++) {
		if (mask == 0) {
			if ((p = header_bytes(a, 1)) == NULL)
				return (-1);
			avail = *p;
			mask = 0x80;
		}
		data[i] = (avail & mask)?1:0;
		mask >>= 1;
	}