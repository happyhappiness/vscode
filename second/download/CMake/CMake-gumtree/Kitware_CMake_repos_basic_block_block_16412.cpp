{
		s1 += l;
		l = p1->ext_len - p2->ext_len;
		while (l--)
			if (0 != *s1++)
				return (*(const unsigned char *)(s1 - 1));
	}