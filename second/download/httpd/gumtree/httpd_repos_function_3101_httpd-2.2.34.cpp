static int BF_decode(BF_word *dst, const char *src, int size)
{
	unsigned char *dptr = (unsigned char *)dst;
	unsigned char *end = dptr + size;
	const unsigned char *sptr = (const unsigned char *)src;
	unsigned int tmp, c1, c2, c3, c4;

	do {
		BF_safe_atoi64(c1, *sptr++);
		BF_safe_atoi64(c2, *sptr++);
		*dptr++ = (c1 << 2) | ((c2 & 0x30) >> 4);
		if (dptr >= end) break;

		BF_safe_atoi64(c3, *sptr++);
		*dptr++ = ((c2 & 0x0F) << 4) | ((c3 & 0x3C) >> 2);
		if (dptr >= end) break;

		BF_safe_atoi64(c4, *sptr++);
		*dptr++ = ((c3 & 0x03) << 6) | c4;
	} while (dptr < end);

	return 0;
}