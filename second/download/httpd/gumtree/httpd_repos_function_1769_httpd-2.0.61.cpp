void
ascii2ebcdic(unsigned char *dest, const unsigned char *srce, size_t count)
{
	while (count-- != 0) {
		*dest++ = os_toebcdic[*srce++];
	}
}