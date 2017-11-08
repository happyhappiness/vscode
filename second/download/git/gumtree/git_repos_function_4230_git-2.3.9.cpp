static int hex2(const char *cp)
{
	if (cp[0] && cp[1])
		return (hex1(cp[0]) << 4) | hex1(cp[1]);
	else
		return -1;
}