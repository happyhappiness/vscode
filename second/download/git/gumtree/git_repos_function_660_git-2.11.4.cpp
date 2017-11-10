static int packet_length(const char *linelen)
{
	int val = hex2chr(linelen);
	return (val < 0) ? val : (val << 8) | hex2chr(linelen + 2);
}