static int get_oid_hex_segment(const char *hex, unsigned int hex_len,
		unsigned char *oid, unsigned int oid_len)
{
	unsigned int i, len = hex_len >> 1;
	if (hex_len % 2 != 0 || len > oid_len)
		return -1;
	for (i = 0; i < len; i++) {
		unsigned int val = (hexval(hex[0]) << 4) | hexval(hex[1]);
		if (val & ~0xff)
			return -1;
		*oid++ = val;
		hex += 2;
	}
	for (; i < oid_len; i++)
		*oid++ = 0;
	return len;
}