{
	size_t fbsize = bsize;

	while (bsize && psize > 1) {
		unsigned char x;

		if (p[0] >= 'a' && p[0] <= 'z')
			x = (p[0] - 'a' + 0x0a) << 4;
		else if (p[0] >= 'A' && p[0] <= 'Z')
			x = (p[0] - 'A' + 0x0a) << 4;
		else if (p[0] >= '0' && p[0] <= '9')
			x = (p[0] - '0') << 4;
		else
			return (-1);
		if (p[1] >= 'a' && p[1] <= 'z')
			x |= p[1] - 'a' + 0x0a;
		else if (p[1] >= 'A' && p[1] <= 'Z')
			x |= p[1] - 'A' + 0x0a;
		else if (p[1] >= '0' && p[1] <= '9')
			x |= p[1] - '0';
		else
			return (-1);
		
		*b++ = x;
		bsize--;
		p += 2;
		psize -= 2;
	}
	return (fbsize - bsize);
}