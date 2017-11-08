static inline int hex2chr(const char *s)
{
	int val = hexval(s[0]);
	return (val < 0) ? val : (val << 4) | hexval(s[1]);
}