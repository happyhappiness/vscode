static int get_hex_color(const char *in, unsigned char *out)
{
	unsigned int val;
	val = (hexval(in[0]) << 4) | hexval(in[1]);
	if (val & ~0xff)
		return -1;
	*out = val;
	return 0;
}