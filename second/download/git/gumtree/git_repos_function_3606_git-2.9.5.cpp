static int prepare_prefixes(const char *name, int len,
			    unsigned char *bin_pfx,
			    char *hex_pfx)
{
	int i;

	hashclr(bin_pfx);
	memset(hex_pfx, 'x', 40);
	for (i = 0; i < len ;i++) {
		unsigned char c = name[i];
		unsigned char val;
		if (c >= '0' && c <= '9')
			val = c - '0';
		else if (c >= 'a' && c <= 'f')
			val = c - 'a' + 10;
		else if (c >= 'A' && c <='F') {
			val = c - 'A' + 10;
			c -= 'A' - 'a';
		}
		else
			return -1;
		hex_pfx[i] = c;
		if (!(i & 1))
			val <<= 4;
		bin_pfx[i >> 1] |= val;
	}
	return 0;
}