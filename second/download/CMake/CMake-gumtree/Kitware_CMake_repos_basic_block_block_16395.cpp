(p1->ext_len < p2->ext_len) {
		s2 += l;
		l = p2->ext_len - p1->ext_len;
		while (l--)
			if (0x20 != *s2++)
				return (0x20
				    - *(const unsigned char *)(s2 - 1));
	} else if (p1->ext_len > p2->ext_len) {
		s1 += l;
		l = p1->ext_len - p2->ext_len;
		while (l--)
			if (0x20 != *s1++)
				return (*(const unsigned char *)(s1 - 1)
				    - 0x20);
	}