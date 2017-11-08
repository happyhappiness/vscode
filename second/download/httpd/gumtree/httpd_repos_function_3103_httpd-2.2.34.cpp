static void BF_swap(BF_word *x, int count)
{
	static int endianness_check = 1;
	char *is_little_endian = (char *)&endianness_check;
	BF_word tmp;

	if (*is_little_endian)
	do {
		tmp = *x;
		tmp = (tmp << 16) | (tmp >> 16);
		*x++ = ((tmp & 0x00FF00FF) << 8) | ((tmp >> 8) & 0x00FF00FF);
	} while (--count);
}